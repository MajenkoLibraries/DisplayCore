#include <JPEG.h>

#define DQT      0xDB    // Define Quantization Table
#define SOF      0xC0    // Start of Frame (size information)
#define DHT      0xC4    // Huffman Table
#define SOI      0xD8    // Start of Image
#define SOS      0xDA    // Start of Scan
#define EOI      0xD9    // End of Image, or End of File
#define APP0     0xE0

#define BYTE_TO_WORD(x) (((x)[0]<<8)|(x)[1])

#define cY    1
#define cCb    2
#define cCr    3

#include <ILI9481.h>
extern ILI9481 tft;

static const int ZigZagArray[64] = 
{
    0,   1,   5,  6,   14,  15,  27,  28,
    2,   4,   7,  13,  16,  26,  29,  42,
    3,   8,  12,  17,  25,  30,  41,  43,
    9,   11, 18,  24,  31,  40,  44,  53,
    10,  19, 23,  32,  39,  45,  52,  54,
    20,  22, 33,  38,  46,  51,  55,  60,
    21,  34, 37,  47,  50,  56,  59,  61,
    35,  36, 48,  49,  57,  58,  62,  63,
};

JPEG::JPEG(const uint8_t *data, uint32_t len) {
    _data = data;
    _len = len;
    _nbits_in_reservoir = 0;
    _reservoir = 0;
}

uint8_t JPEG::clamp(int i) {
    if (i<0)
        return 0;
    else if (i>255)
        return 255;
    else
        return i;
}   

bool JPEG::parseSOF(const uint8_t *stream) {
    int height = BYTE_TO_WORD(stream+3);
    int width  = BYTE_TO_WORD(stream+5);
    int nr_components = stream[7];

    stream += 8;
    for (int i=0; i<nr_components; i++) {
        int cid                = *stream++;
        int sampling_factor     = *stream++;
        int Q_table            = *stream++;

        _componentInfo[cid].m_vFactor = sampling_factor&0xf;
        _componentInfo[cid].m_hFactor = sampling_factor>>4;
        _componentInfo[cid].m_qTable = _qTables[Q_table];
    }
    _width = width;
    _height = height;

    return true;
}

void JPEG::buildQuantizationTable(float *qtable, const uint8_t *ref_table) {
    int c = 0;

    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            qtable[c] = ref_table[c];
            c++;
        }
    }
}

bool JPEG::parseDQT(const uint8_t *stream) {
    int length, qi;
    float *table;

    length = BYTE_TO_WORD(stream) - 2;
    stream += 2;    // Skip length

    while (length>0) {
        qi = *stream++;

        int qprecision = qi>>4;     // upper 4 bits specify the precision
        int qindex     = qi&0xf; // index is lower 4 bits

        if (qprecision) {
            return false;
        }

        if (qindex>4) {
            return false;
        }

        buildQuantizationTable(_qTables[qindex], stream);
        stream += 64;
        length -= 65;
    }
    return true;
}

bool JPEG::parseSOS(const uint8_t *stream) {
    uint32_t nr_components = stream[2];

    if (nr_components != 3) {
        return false;
    }

    stream += 3;
    for (uint32_t i=0;i<nr_components;i++) {
        uint32_t cid   = *stream++;
        uint32_t table = *stream++;

        if ((table&0xf)>=4) {
            return false;
        }
        if ((table>>4)>=4) {
            return false;
        }

        _componentInfo[cid].m_acTable = &_HTAC[table&0xf];
        _componentInfo[cid].m_dcTable = &_HTDC[table>>4];
    }
    _stream = stream+3;
    return true;
}

void JPEG::genHuffCodes(int num_codes, stBlock* arr, uint8_t *huffVal ) {
     int hufcounter = 0;
     int codelengthcounter = 1;
 
     for(int cc=0; cc< num_codes; cc++) {
         while ( arr[cc].length > codelengthcounter ) {
            hufcounter = hufcounter << 1;
            codelengthcounter++;
         }

         arr[cc].code = hufcounter;
         arr[cc].value = huffVal[cc];
         hufcounter = hufcounter + 1;
    }
}

void JPEG::buildHuffmanTable(const uint8_t *bits, const uint8_t *stream, stHuffmanTable *HT) {
    for (int j=1; j<=16; j++) {
        HT->m_length[j] = bits[j];
    }

    // Work out the total number of codes
    int numBlocks = 0;
    for (int i=1; i<=16; i++) {
        numBlocks += HT->m_length[i];
    }
    HT->m_numBlocks = numBlocks;

    // Fill in the data our our blocks, so we know how many bits each
    // one is
    int c=0;
    for (int i=1; i<=16; i++) {
        for (int j=0; j<HT->m_length[i]; j++) {
            HT->m_blocks[c].length = i;
            c++;
        }

    }

    genHuffCodes(HT->m_numBlocks, HT->m_blocks, HT->m_hufVal);
}

bool JPEG::parseDHT(const uint8_t *stream) {
    uint32_t count, i;
    uint8_t huff_bits[17];
    int length, index;

    length = BYTE_TO_WORD(stream) - 2;
    stream += 2;  

    while (length>0) {
        index = *stream++;

        // We need to calculate the number of bytes 'vals' will takes
        huff_bits[0] = 0;
        count = 0;
        for (i=1; i<17; i++) {
            huff_bits[i] = *stream++;
            count += huff_bits[i];
        }

        if (count > 256) {
            return false;
        }
        if ( (index &0xf) >= HUFFMAN_TABLES) {
            return false;
        }

        if (index & 0xf0 ) {
            uint8_t *huffval = _HTAC[index&0xf].m_hufVal;
            for (i = 0; i < count; i++)
                huffval[i] = *stream++;
            buildHuffmanTable(huff_bits, stream, &_HTAC[index&0xf]); // AC
        } else {
            uint8_t *huffval = _HTDC[index&0xf].m_hufVal;
            for (i = 0; i < count; i++)
                huffval[i] = *stream++;
            buildHuffmanTable(huff_bits, stream, &_HTDC[index&0xf]); // DC
        }

        length -= 1;
        length -= 16;
        length -= count;
    }
    return true;
}

bool JPEG::parseJFIF(const uint8_t *stream) {
    int chuck_len;
    int marker;
    int sos_marker_found = 0;
    int dht_marker_found = 0;

    // Parse marker
    while (!sos_marker_found) {
        if (*stream++ != 0xff) {
            return false;
        }

        // Skip any padding ff byte (this is normal)
        while (*stream == 0xff) {
            stream++;
        }

        marker = *stream++;
        chuck_len = BYTE_TO_WORD(stream);

        switch (marker)
        {
            case SOF:
                if (!parseSOF(stream))
                    return false;
                break;

            case DQT:
                if (!parseDQT(stream))
                    return false;
                break;

            case SOS:
                if (!parseSOS(stream))
                    return false;
                sos_marker_found = 1;
                break;

            case DHT:
                if (!parseDHT(stream))
                    return false;
                dht_marker_found = 1;
                break;

            // The reason I added these additional skips here, is because for
            // certain jpg compressions, like swf, it splits the encoding 
            // and image data with SOI & EOI extra tags, so we need to skip
            // over them here and decode the whole image
            case SOI:
            case EOI:
                chuck_len = 0;
                break;

            break;

            case 0xDD: //DRI: Restart_markers=1;
                break;

            case APP0:
                break;

            default:
                break;
        }

        stream += chuck_len;
    }

    if (!dht_marker_found) {
        return false;
    }

    return true;
}

bool JPEG::parseHeader() {
    if (_data[0] != 0xFF) {
        return false;
    }
    if (_data[1] != SOI) {
        return false;
    }

    const uint8_t *startStream = _data+2;
    const int fileSize = _len - 2;
    return parseJFIF(startStream);
}

void JPEG::draw(DisplayCore *dev, int x, int y, color_t t) {
    draw(dev, x, y);
}

void JPEG::drawTransformed(DisplayCore *dev, int x, int y, int transform) {
    draw(dev, x, y);
}

void JPEG::drawTransformed(DisplayCore *dev, int x, int y, int transform, color_t t) {
    draw(dev, x, y);
}

void JPEG::fillNBits(const uint8_t **stream, int &nbits_wanted) {
    while (_nbits_in_reservoir < nbits_wanted) {
        const unsigned char c = *(*stream)++;
        _reservoir <<= 8;
        if (c == 0xff && (**stream) == 0x00)
            (*stream)++;
        _reservoir |= c;
        _nbits_in_reservoir+=8;
    }
}

int JPEG::lookNBits(const uint8_t **stream, int nbits_wanted) {
    fillNBits(stream, nbits_wanted);

    int result = ((_reservoir)>>(_nbits_in_reservoir-(nbits_wanted)));
    return result;
}

short JPEG::getNBits(const uint8_t **stream, int nbits_wanted) {
    fillNBits(stream, nbits_wanted);
    
    short result = ((_reservoir)>>(_nbits_in_reservoir-(nbits_wanted))); 

    _nbits_in_reservoir -= (nbits_wanted); 
    _reservoir &= ((1U<<_nbits_in_reservoir)-1);

    return result;
}

void JPEG::skipNBits(const uint8_t **stream, int &nbits_wanted) {
    fillNBits(stream, nbits_wanted);

    _nbits_in_reservoir -= (nbits_wanted); 
    _reservoir &= ((1U<<_nbits_in_reservoir)-1);
}


bool JPEG::isInHuffmanCodes(int code, int numCodeBits, int numBlocks, stBlock* blocks, int* outValue) {
    for (int j=0; j<numBlocks; j++) {
        int hufhCode        = blocks[j].code;
        int hufCodeLenBits    = blocks[j].length;
        int hufValue        = blocks[j].value;

        // We've got a match!
        if ((code==hufhCode) && (numCodeBits==hufCodeLenBits)) {
            *outValue = hufValue;
            return true;
        }
    }
    return false;
}

void JPEG::processHuffmanDataUnit(int indx) {
    stComponent *c = &_componentInfo[indx];
    short DCT_tcoeff[64];
    memset(DCT_tcoeff, 0, sizeof(DCT_tcoeff)); //Initialize DCT_tcoeff
    bool found = false;
    int decodedValue = 0;
    for (int k=1; k<16; k++) {
        int code = lookNBits(&_stream, k);
        if (isInHuffmanCodes(code, k,  c->m_dcTable->m_numBlocks, c->m_dcTable->m_blocks, &decodedValue)) {
            skipNBits(&_stream, k);
            found = true;
            int numDataBits = decodedValue;
            if (numDataBits==0) {
                DCT_tcoeff[0] = c->m_previousDC;
            } else {
                short data = getNBits(&_stream, numDataBits);

                data = determineSign(data, numDataBits);

                DCT_tcoeff[0] = data + c->m_previousDC;
                c->m_previousDC = DCT_tcoeff[0];
            }

            // Found so we can exit out
            break;
        }
    }

    if (!found) {
        return;
    }

    // Second, the 63 AC coefficient
    int nr=1; 
    bool EOB_found=false;
    while ( (nr<=63)&&(!EOB_found) ) {
        int k = 0;
        for (k=1; k<=16; k++) {
            // Keep grabbing one bit at a time till we find one thats a huffman code
            int code = lookNBits(&_stream, k);


            // Check if its one of our huffman codes
            if (isInHuffmanCodes(code, k,  c->m_acTable->m_numBlocks, c->m_acTable->m_blocks, &decodedValue)) {

                // Skip over k bits, since we found the huffman value
                skipNBits(&_stream, k);


                // Our decoded value is broken down into 2 parts, repeating RLE, and then
                // the number of bits that make up the actual value next
                int valCode = decodedValue;

                unsigned char size_val = valCode&0xF;    // Number of bits for our data
                unsigned char count_0  = valCode>>4;    // Number RunLengthZeros

                if (size_val == 0) {// RLE 
                    if (count_0 == 0) {
                        EOB_found = true;
                    } else if (count_0==0xF) {
                        nr+=16;
                    }
                } else {
                    nr += count_0; //skip count_0 zeroes
                    
                    if (nr > 63) {
                        return;
                    }

                    short data = getNBits(&_stream, size_val );

                    data = determineSign(data, size_val);

                    DCT_tcoeff[nr++]=data;

                }
                break;
            }
        }

        if (k>16) {    
            nr++;
        }
    }

    // We've decoded a block of data, so copy it across to our buffer
    for (int j = 0; j < 64; j++) {
        c->m_DCT[j] = DCT_tcoeff[j];
    }
}

int JPEG::determineSign(int val, int nBits) {
    bool negative = val < (1<<(nBits-1));

    if (negative) {
        val = val + (-1 << (nBits)) + 1; 
    }
    return val;
}

float JPEG::C(int u) {
    if (u == 0)
         return (1.0f/sqrtf(2));
    else
         return 1.0f;
}

int JPEG::func(int x, int y, const int block[8][8]) {
    float sum=0;
    for( int u=0; u<8; u++) {
         for(int v=0; v<8; v++) {
             sum += ( C(u) * C(v) ) * block[u][v] * cosf( ((2*x+1) * u * PI) / 16)  * cosf( ((2*y+1) * v * PI) / 16);
         }
    }         
    return (int) ((1.0/4.0) * sum);
}

void JPEG::performIDCT(int outBlock[8][8], const int inBlock[8][8]) {
    for(int y=0; y<8; y++) {
        for(int x=0; x<8; x++) {
            outBlock[x][y]  =  func( x, y, inBlock);
        }
    }
}

void JPEG::transformArray(int outArray[8][8], const int inArray[64]) {
    int cc = 0;
    for( int y=0; y<8; y++) {
        for( int x=0; x<8; x++) {
            outArray[x][y]  =  inArray[cc];
            cc++;
        }
    }
}

void JPEG::deZigZag(int *outBlock, const int *inBlock) {
    for(int i=0; i<64; i++) {
        outBlock[ i ] = inBlock[ZigZagArray[i]];
    }
}

void JPEG::dequantizeBlock(int *block, const float *quantBlock) {
    for( int c=0; c<64; c++) {
        block[c] = (int)(block[c] * quantBlock[c]);
    }
}

void JPEG::decodeSingleBlock(stComponent *comp, uint8_t *outputBuf, int stride) {
    short* inptr    = comp->m_DCT;
    float* quantptr = comp->m_qTable;


    // Create a temp 8x8, i.e. 64 array for the data
    int data[64] = {0};

    // Copy our data into the temp array
    for (int i=0; i<64; i++) {
        data[i] = inptr[i];
    }

    // De-Quantize
    dequantizeBlock(data, quantptr);

    // De-Zig-Zag
    int block[64] = {0};
    deZigZag(block, data);

    // Create an 8x8 array
    int arrayBlock[8][8]={0};
    transformArray(arrayBlock, block);

    // Inverse DCT
    int val[8][8]={0};
    performIDCT(val, arrayBlock);

    // Level Shift each element (i.e. add 128), and copy to our
    // output
    unsigned char *outptr = outputBuf;
    for (int y = 0; y < 8; y++) {
        for (int x=0; x<8; x++)
        {
            val[x][y] += 128;

            outptr[x] = clamp(val[x][y]);
        }

        outptr += stride;
    }
}

void JPEG::decodeMCU(int w, int h) {
    // Y
    for (int y=0; y<h; y++) {
        for (int x=0; x<w; x++) {
            int stride = w*8;
            int offset = x*8 + y*64*w;

            processHuffmanDataUnit(cY);

            decodeSingleBlock(&_componentInfo[cY], &_Y[offset], stride);
        }
    }

    // Cb
    processHuffmanDataUnit(cCb);
    decodeSingleBlock(&_componentInfo[cCb], _Cb, 8);

    // Cr
    processHuffmanDataUnit(cCr);
    decodeSingleBlock(&_componentInfo[cCr], _Cr, 8);
}

color_t JPEG::convertYCrCbto565(int y, int cb, int cr) {
    float red, green, blue;

    red   = y + 1.402f*(cb-128);
    green = y-0.34414f*(cr-128)-0.71414f*(cb-128);
    blue  = y+1.772f*(cr-128);

    uint8_t r = (int) clamp((int)red);
    uint8_t g = (int) clamp((int)green);
    uint8_t b = (int) clamp((int)blue);
    return rgb(r, g, b);
}

void JPEG::draw(DisplayCore *dev, int px, int py) {
    if (!parseHeader()) {
        return;
    }

    int hFactor = _componentInfo[cY].m_hFactor;
    int vFactor = _componentInfo[cY].m_vFactor;

    _componentInfo[0].m_previousDC = 0;
    _componentInfo[1].m_previousDC = 0;
    _componentInfo[2].m_previousDC = 0;
    _componentInfo[3].m_previousDC = 0;

    int xstride_by_mcu = hFactor * 8;
    int ystride_by_mcu = vFactor * 8;

    unsigned int bytes_per_blocklines = _width * 3 * ystride_by_mcu;
    unsigned int bytes_per_mcu = xstride_by_mcu * 3;

//    uint8_t colorspace[ystride_by_mcu * xstride_by_mcu];

    for (int y = 0; y < _height; y += ystride_by_mcu) {
        for (int x = 0; x < _width; x += xstride_by_mcu) {
            decodeMCU(hFactor, vFactor);

            dev->openWindow(x, y, xstride_by_mcu, ystride_by_mcu);

            for (int yy = 0; yy < ystride_by_mcu; yy++) {
                for (int xx = 0; xx < xstride_by_mcu; xx++) {
                    int Y =  _Y[yy * xstride_by_mcu + xx];
                    int Cr =  _Cr[yy * xstride_by_mcu + xx];
                    int Cb =  _Cb[yy * xstride_by_mcu + xx];
                    dev->windowData(convertYCrCbto565(Y,Cr,Cb));
                }
            }
            dev->closeWindow();
//
//            YCrCB_to_RGB24_Block8x8(hFactor, vFactor, x, y, _width, _height);
        }
    }
    
}


