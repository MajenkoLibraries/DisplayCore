#ifndef _JPEG_H
#define _JPEG_H

#include <DisplayCore.h>

#define HUFFMAN_TABLES        4
#define COMPONENTS            4

struct stBlock {
     int value; 
     int length;
     unsigned short int code;
};

struct stHuffmanTable {
    unsigned char    m_length[17];
    unsigned char    m_hufVal[257];
    int                m_numBlocks;
    stBlock            m_blocks[1024];
};

struct stComponent {
    unsigned int            m_hFactor;
    unsigned int            m_vFactor;
    float *                 m_qTable; 
    stHuffmanTable*         m_acTable;
    stHuffmanTable*         m_dcTable;
    short int               m_DCT[65]; 
    int                     m_previousDC;
};

class JPEG : public Image {
    private:
        const uint8_t *_data;
        const uint8_t *_stream;
        uint32_t _len;

        stComponent _componentInfo[COMPONENTS];
        float _qTables[COMPONENTS][64];
        stHuffmanTable _HTDC[HUFFMAN_TABLES];
        stHuffmanTable _HTAC[HUFFMAN_TABLES];

        uint8_t _Y[64*4];
        uint8_t _Cr[64*4];
        uint8_t _Cb[64*4];

        uint32_t _reservoir;
        uint32_t _nbits_in_reservoir;

        bool parseHeader();
        void buildQuantizationTable(float *, const uint8_t *);
        void buildHuffmanTable(const uint8_t *, const uint8_t *, stHuffmanTable *);
        void genHuffCodes(int, stBlock *, uint8_t *);
        void processHuffmanDataUnit(int indx);
        int lookNBits(const uint8_t **, int);
        void fillNBits(const uint8_t **, int &);
        void skipNBits(const uint8_t **, int &);
        short getNBits(const uint8_t **, int); 

        bool isInHuffmanCodes(int, int, int, stBlock *, int *);
        int determineSign(int, int);

        color_t convertYCrCbto565(int y, int cb, int cr);
        uint8_t clamp(int i);
        float C(int u);
        int func(int x, int y, const int block[8][8]);
        void performIDCT(int outBlock[8][8], const int inBlock[8][8]);
        void transformArray(int outArray[8][8], const int inArray[64]);
        void deZigZag(int *, const int *);
        void dequantizeBlock(int *, const float *);
        void decodeSingleBlock(stComponent *, uint8_t *, int);

        void decodeMCU(int, int);



        bool parseJFIF(const uint8_t *);
        bool parseSOF(const uint8_t *);
        bool parseDQT(const uint8_t *);
        bool parseDHT(const uint8_t *);
        bool parseSOS(const uint8_t *);

    public:
        JPEG(const uint8_t *data, uint32_t len);
        void draw(DisplayCore *dev, int x, int y);
        void draw(DisplayCore *dev, int x, int y, color_t t);
        void drawTransformed(DisplayCore *dev, int x, int y, int transform);
        void drawTransformed(DisplayCore *dev, int x, int y, int transform, color_t t);
};

#endif
