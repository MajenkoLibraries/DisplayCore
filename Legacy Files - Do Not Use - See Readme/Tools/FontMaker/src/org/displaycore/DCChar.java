package org.displaycore;

import javax.swing.*;
import javax.swing.border.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.math.*;

class DCChar extends JComponent {
    int characterWidth;
    int bitsPerPixel;
    int characterHeight; // Fixed and set by the DCFont that generated it.
    int bytesPerLine;
    ArrayList<BigInteger> characterData;
    boolean selected = false;
    int glyphNumber;

    public DCChar(int gn, int w, int h, int bpp, int bpl, ArrayList<BigInteger> d) {
        bitsPerPixel = bpp;
        glyphNumber = gn;
        characterWidth = w;
        characterHeight = h;
        characterData = d;
        bytesPerLine = bpl;
    }

    public void setBorder(Border b) {
    }

    public void paintComponent(Graphics g) {
        BufferedImage offscreen = new BufferedImage(characterWidth + 2, characterHeight + 2, BufferedImage.TYPE_INT_RGB);
        Graphics2D graphic = offscreen.createGraphics();
        graphic.fillRect(0, 0, characterWidth + 2, characterHeight + 2);

        graphic.setColor(new Color(0, 0, 0));

        Integer bm = (1 << bitsPerPixel) - 1;
        BigInteger bitMask = BigInteger.valueOf(bm.intValue());

        for (int y = 0; y < characterHeight; y++) {
            BigInteger v = characterData.get(y);

            for (int pixelNumber = 0; pixelNumber < characterWidth; pixelNumber++) {
                BigInteger pv = v.and(bitMask);
                int pixelValue = pv.intValue();
                int brightness = 255 - (255 * pixelValue / bitMask.intValue());
                if (selected) {
                    graphic.setColor(new Color(brightness / 5 * 4, brightness, brightness / 5 * 4));
                } else {
                    graphic.setColor(new Color(brightness, brightness, brightness));
                }
                graphic.drawLine(pixelNumber, y + 1, pixelNumber, y + 1);
                v = v.shiftRight(bitsPerPixel);
            }
        }
        g.drawImage(offscreen, 0, 0, null);
    }

    public void setPixel(Point p, int col) {
        setPixel(p.x, p.y, col);
    }

    public void setPixel(int x, int y, int col) {
        BigInteger lv = characterData.get(y);
        Integer maskSize = (1 << bitsPerPixel) - 1;
        Integer color = col;
        BigInteger mask = BigInteger.valueOf(maskSize.intValue());
        BigInteger colorBlock = BigInteger.valueOf(color.intValue());
        mask = mask.shiftLeft(x * bitsPerPixel);
        colorBlock = colorBlock.shiftLeft(x * bitsPerPixel);

        lv = lv.and(mask.not());
        lv = lv.or(colorBlock);
        characterData.set(y, lv);
        repaint();
    }

    public int getPixel(Point p) {
        return getPixel(p.x, p.y);
    }

    public int getPixel(int x, int y) {
        Integer bm = (1 << bitsPerPixel) - 1;
        BigInteger bitMask = BigInteger.valueOf(bm.intValue());
        BigInteger v = characterData.get(y);
        for (int i = 0; i < x; i++) {
            v = v.shiftRight(bitsPerPixel);
        }
        BigInteger pv = v.and(bitMask);
        int pixelValue = pv.intValue();
        return pixelValue;
    }

    public Dimension getPreferredSize() {
        return new Dimension(characterWidth + 2, characterHeight + 2);
    }

    public Dimension getMinimumSize() {
        return new Dimension(characterWidth + 2, characterHeight + 2);
    }
        
    public Dimension getMaximumSize() {
        return new Dimension(characterWidth + 2, characterHeight + 2);
    }

    public int getGlyphNumber() {
        return glyphNumber;
    }

    public int getWidth() {
        return characterWidth;
    }

    public void setWidth(int v) {
        characterWidth = v;
        repaint();
    }

    public boolean isSelected() {
        return selected;
    }

    public void setSelected(boolean s) {
        selected = s;
    }

    public void scrollUp() {
        BigInteger topLine = characterData.remove(0);
        characterData.add(topLine);
        repaint();
    }

    public void scrollDown() {
        BigInteger bottomLine = characterData.remove(characterHeight - 1);
        characterData.add(0, bottomLine);
        repaint();
    }

    public void scrollLeft() {
        for (int line = 0; line < characterHeight; line++) {
            int leftmostPixel = getPixel(0, line);
            BigInteger lineValue = characterData.get(line);
            lineValue = lineValue.shiftRight(bitsPerPixel);
            characterData.set(line, lineValue);
            setPixel(characterWidth - 1, line, leftmostPixel);
        }
        repaint();
    }

    public void scrollRight() {
        for (int line = 0; line < characterHeight; line++) {
            int rightmostPixel = getPixel(characterWidth - 1, line);
            BigInteger lineValue = characterData.get(line);
            lineValue = lineValue.shiftLeft(bitsPerPixel);
            characterData.set(line, lineValue);
            setPixel(0, line, rightmostPixel);
        }
        repaint();
    }

    public String getFontData() {
        StringBuilder b = new StringBuilder();
        BigInteger byteMask = BigInteger.valueOf(0xff);
        for (int line = 0; line < characterHeight; line++) {
            BigInteger lineData = characterData.get(line);
            String linePart = "";
            for (int chunk = 0; chunk < bytesPerLine; chunk++) {
                BigInteger aByte = lineData.and(byteMask);
                lineData = lineData.shiftRight(8);
                int bVal = aByte.intValue();
                linePart = bVal + ", " + linePart;
            }
            b.append(linePart);
        }
        return b.toString();
    }

    public void shiftAndCrop() {

        // First scroll it left until it butts up against the edge.

        int maxIter = characterWidth;
        while (maxIter > 0) {
            boolean hasPixel = false;
            for (int i = 0; i < characterHeight; i++) {
                if (getPixel(0, i) > 0) {
                    hasPixel = true;
                }
            }
            if (hasPixel) {
                break;
            }
            scrollLeft();
            maxIter--;
        }

        // Now find the right-most pixel.

        while (characterWidth > 0) {
            boolean hasPixel = false;
            for (int i = 0; i < characterHeight; i++) {
                if (getPixel(characterWidth - 1, i) > 0) {
                    hasPixel = true;
                }
            }
            if (hasPixel) {
                break;
            }
            characterWidth--;
        }
        characterWidth ++;
        repaint();
    }

    public void setHeight(int h) {
        characterHeight = h;
        while (characterData.size() < h) {
            characterData.add(BigInteger.ZERO);
        }
    }
}

