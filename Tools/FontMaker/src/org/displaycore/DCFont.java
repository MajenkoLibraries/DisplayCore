package org.displaycore;

import java.io.*;
import java.util.*;
import java.util.regex.*;
import java.math.*;

class DCFont {
    public int linesPerCharacter;
    public int bytesPerLine;
    public int startGlyph;
    public int endGlyph;
    public int bitsPerPixel;
    public String fontName;

    public ArrayList<DCChar> characters;

    public DCFont(String filename) {
        loadFontFile(filename);
    }

    public DCFont(File file) {
        loadFontFile(file);
    }

    public boolean loadFontFile(String filename) {
        return loadFontFile(new File(filename));
    }

    public boolean loadFontFile(File file) {
        characters = new ArrayList<DCChar>();
        if (!file.exists()) {
            return false;
        }

        StringBuilder incomingLines = new StringBuilder();
        try {
            FileReader fr = new FileReader(file);
            BufferedReader br = new BufferedReader(fr);
            String line;
            while((line = br.readLine()) != null) {
                line = line.trim();
                if (line.contains("//")) {
                    line = line.substring(0, line.indexOf("//"));
                }
                incomingLines.append(line);
            }
            br.close();
            fr.close();
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }

        String data = incomingLines.toString();

        // const uint8_t Atari[]
        Pattern p = Pattern.compile("const\\s+uint8_t\\s+(.*)\\[\\]");
        Matcher m = p.matcher(data);
        
        fontName = null;

        if (m.find()) {
            fontName = m.group(1).trim();
        }

        if (fontName == null) {
            // const uint8_t *Atari =
            p = Pattern.compile("const\\s+uint8_t\\s*\\*([^=\\s]*)\\s*=");
            m = p.matcher(data);
            
            if (m.find()) {
                fontName = m.group(1).trim();
            }
        }

        // Strip block comments - TODO

        // Extract inner block of data

        p = Pattern.compile("\\{([^{}]+)\\}");
        m = p.matcher(data);
        if (m.find()) {
            data = m.group(1);
        } else {
            return false;
        }
        String[] bytes = data.split(",");

        linesPerCharacter = parseValue(bytes[0]);
        bytesPerLine = parseValue(bytes[1]);
        startGlyph = parseValue(bytes[2]);
        endGlyph = parseValue(bytes[3]);
        bitsPerPixel = parseValue(bytes[4]);

        int byteNo = 5;
        for (int i = startGlyph; i <= endGlyph; i++) {
            int width = parseValue(bytes[byteNo++]);
            ArrayList<BigInteger> cdata = new ArrayList<BigInteger>();
            for (int j = 0; j < linesPerCharacter; j++) {
                BigInteger lineValue = BigInteger.ZERO;
                for (int k = 0; k < bytesPerLine; k++) {
                    Integer vi = parseValue(bytes[byteNo++]);
                    BigInteger v = BigInteger.valueOf(vi.intValue());
                    v = v.shiftLeft((bytesPerLine - k - 1)*8);
                    lineValue = lineValue.or(v);
                }
                cdata.add(lineValue);
            }
            DCChar ch = new DCChar(i, width, linesPerCharacter, bitsPerPixel, cdata);
            characters.add(ch);
    
        }
            
        return true;
    }

    int parseValue(String v) {
        int val = 0;
        v = v.trim();
        v = v.toLowerCase();
        if (v.startsWith("0b")) {           // Binary
            try { val = Integer.parseInt(v.substring(2), 2); } catch (Exception e) { }
        } else if (v.startsWith("0x")) {    // Hex
            try { val = Integer.parseInt(v.substring(2), 16); } catch (Exception e) { }
        } else if (v.startsWith("0")) {     // Octal
            try { val = Integer.parseInt(v.substring(1), 8); } catch (Exception e) { }
        } else {                            // Decimal
            try { val = Integer.parseInt(v, 10); } catch (Exception e) { }
        }
        return val;
    }

    public String getName() {
        return fontName;
    }

    public int getHeight() {
        return linesPerCharacter;
    }

    public int getWidth() {
        return bytesPerLine * 8 / bitsPerPixel;
    }

    public int getDepth() {
        return bitsPerPixel;
    }
    
    public void selectGlyph(DCChar ch) {
        for (DCChar ach : characters) {
            if (ach.equals(ch)) {
                ach.setSelected(true);
            } else {
                ach.setSelected(false);
            }
        }
    }
}
