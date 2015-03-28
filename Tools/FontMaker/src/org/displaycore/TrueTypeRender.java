package org.displaycore;

import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import javax.swing.filechooser.*;
import java.awt.image.*;
import java.awt.font.*;
import java.awt.geom.*;
import java.math.*;

public class TrueTypeRender extends JDialog {

    static File lastOpenLocation;

    JFrame parent;
    JTextArea fontNameBox;
    Font loadedFont;
    File ttfFile;
    JSpinner fontSizeBox;
    JSpinner fontDepthBox;
    JSpinner firstGlyph;
    JSpinner lastGlyph;
    BufferedImage preview;
    JLabel previewImage;
    JLabel infoBox;

    class Glyph {
        int value;
 
        public Glyph(int v) {
            value = v;
        }

        public int getValue() {
            return value;
        }

        public String toString() {
            char c = (char)value;
            switch (value) {
                case 0: return value + " - NUL";
                case 1: return value + " - SOH";
                case 2: return value + " - STX";
                case 3: return value + " - ETX";
                case 4: return value + " - EOT";
                case 5: return value + " - ENQ";
                case 6: return value + " - ACK";
                case 7: return value + " - BEL";
                case 8: return value + " - BS";
                case 9: return value + " - TAB";
                case 10: return value + " - LF";
                case 11: return value + " - VT";
                case 12: return value + " - FF";
                case 13: return value + " - CR";
                case 14: return value + " - SO";
                case 15: return value + " - SI";
                case 16: return value + " - DLE";
                case 17: return value + " - DC1";
                case 18: return value + " - DC2";
                case 19: return value + " - DC3";
                case 20: return value + " - DC4";
                case 21: return value + " - NAK";
                case 22: return value + " - SYN";
                case 23: return value + " - ETB";
                case 24: return value + " - CAN";
                case 25: return value + " - EM";
                case 26: return value + " - SUB";
                case 27: return value + " - ESC";
                case 28: return value + " - FS";
                case 29: return value + " - GS";
                case 30: return value + " - RS";
                case 31: return value + " - US";
                case 32: return value + " - SPACE";
                default:
                    return value + " - " + c;
            }
        }
    }

    Glyph[] glyphList;

    public TrueTypeRender(JFrame p) {
        super(p, JDialog.ModalityType.APPLICATION_MODAL);
        parent = p;
        glyphList = new Glyph[256];
        for (int i = 0; i < 256; i++) {
            glyphList[i] = new Glyph(i);
        }
    }

    public void open() {
        setTitle("Render TrueType Font");
        setLayout(new BorderLayout());

        JPanel buttonBox = new JPanel();
        buttonBox.setLayout(new FlowLayout(FlowLayout.RIGHT));

        infoBox = new JLabel();
        buttonBox.add(infoBox);
        
        JButton cancelButton = new JButton("Cancel");
        cancelButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                TrueTypeRender.this.dispose();
            }
        });
        buttonBox.add(cancelButton);

        JButton importButton = new JButton("Render Font");
        importButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (loadedFont != null) {
                    renderFont();
                }
            }
        });
        buttonBox.add(importButton);

        add(buttonBox, BorderLayout.SOUTH);

        JPanel centerBox = new JPanel();
        centerBox.setLayout(new GridBagLayout());
        centerBox.setBorder(new EmptyBorder(10, 10, 10, 10));
        GridBagConstraints c = new GridBagConstraints();

        c.gridx = 0;
        c.gridy = 0;
        c.gridwidth = 1;
        c.gridheight = 1;
        c.weightx = 0D;
        c.fill = GridBagConstraints.HORIZONTAL;
        centerBox.add(new JLabel("Font: "), c);

        c.gridx = 1;
        fontNameBox = new JTextArea();
        fontNameBox.setText("No font selected");
        c.weightx = 1.0D;
        //setComponentWidth(fontNameBox, 300);
        centerBox.add(fontNameBox, c);
     
        c.gridx = 2;
        c.weightx = 0D;
        JButton selectFileButton = new JButton("Select...");
        selectFileButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                JFileChooser fc = new JFileChooser();
                if (lastOpenLocation == null) {
                    lastOpenLocation = new File(System.getProperty("user.dir"));
                }
                fc.setCurrentDirectory(lastOpenLocation);
                FileNameExtensionFilter filter = new FileNameExtensionFilter(
                    "TrueType Font Files", "ttf");
                fc.setFileFilter(filter);
                int rv = fc.showOpenDialog(TrueTypeRender.this);
                if (rv == JFileChooser.APPROVE_OPTION) {
                    ttfFile = fc.getSelectedFile();
                    lastOpenLocation = ttfFile.getParentFile();
                    updateFontData();
                }
            }
        });
        centerBox.add(selectFileButton, c);

        c.gridy++;

        c.gridx = 0;
        c.weightx = 0D;
        c.gridwidth = 1;
        centerBox.add(new JLabel("Font Size: "), c);
        c.gridx = 1;
        c.gridwidth = 3;
        c.weightx = 1D;

        fontSizeBox = new JSpinner();
        fontSizeBox.setValue(20);
        centerBox.add(fontSizeBox, c);

        fontSizeBox.addChangeListener(new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                int fs = (Integer)fontSizeBox.getValue();
                if (fs < 6) {
                    fontSizeBox.setValue(6);
                    fs = 6;
                }
                if (fs > 127) {
                    fontSizeBox.setValue(127);
                    fs = 127;
                }
                renderFontSample();
                infoBox.setText("Estimated " + calculateSize() + " bytes");
                fontNameBox.setText(loadedFont.getFontName().replace(" ", "") + fs);
            }
        });

        c.gridy++;

        c.gridx = 0;
        c.weightx = 0D;
        c.gridwidth = 1;
        centerBox.add(new JLabel("Colours: "), c);
        c.gridx = 1;
        c.gridwidth = 3;
        c.weightx = 1D;

        Integer[] validColors = { 2, 4, 16 };
        SpinnerListModel depthModel = new SpinnerListModel(Arrays.asList(validColors));
        fontDepthBox = new JSpinner(depthModel);
        fontDepthBox.setValue(2);
        centerBox.add(fontDepthBox, c);

        fontDepthBox.addChangeListener(new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                renderFontSample();
                infoBox.setText("Estimated " + calculateSize() + " bytes");
            }
        });

        c.gridy++;

        c.gridx = 0;
        c.weightx = 0D;
        c.gridwidth = 1;
        centerBox.add(new JLabel("First Glyph: "), c);
        c.gridx = 1;
        c.gridwidth = 3;
        c.weightx = 1D;

        SpinnerListModel firstGlyphModel = new SpinnerListModel(Arrays.asList(glyphList));
        firstGlyph = new JSpinner(firstGlyphModel);
        firstGlyph.setValue(glyphList[32]);

        centerBox.add(firstGlyph, c);

        firstGlyph.addChangeListener(new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                int fv = ((Glyph)firstGlyph.getValue()).getValue();
                int lv = ((Glyph)lastGlyph.getValue()).getValue();
                if (fv < 0) {
                    firstGlyph.setValue(glyphList[0]);
                    fv = 0;
                }
                if (fv > lv) {
                    System.err.println("First bigger than last");
                    firstGlyph.setValue(glyphList[lv]);
                    fv = lv;
                }
                infoBox.setText("Estimated " + calculateSize() + " bytes");
            }
        });

        c.gridy++;

        c.gridx = 0;
        c.weightx = 0D;
        c.gridwidth = 1;
        centerBox.add(new JLabel("Last Glyph: "), c);
        c.gridx = 1;
        c.gridwidth = 3;
        c.weightx = 1D;

        SpinnerListModel lastGlyphModel = new SpinnerListModel(Arrays.asList(glyphList));
        lastGlyph = new JSpinner(lastGlyphModel);
        lastGlyph.setValue(glyphList[127]);

        centerBox.add(lastGlyph, c);

        lastGlyph.addChangeListener(new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                int fv = ((Glyph)firstGlyph.getValue()).getValue();
                int lv = ((Glyph)lastGlyph.getValue()).getValue();
                if (lv > 255) {
                    lastGlyph.setValue(glyphList[255]);
                    lv = 0;
                }
                if (lv < fv) {
                    System.err.println("Last smaller than first");
                    lastGlyph.setValue(glyphList[fv]);
                    lv = fv;
                }
                infoBox.setText("Estimated " + calculateSize() + " bytes");
            }
        });

        preview = new BufferedImage(450, 80, BufferedImage.TYPE_BYTE_GRAY);
        previewImage = new JLabel(new ImageIcon(preview));

        c.gridy++;
        c.gridx = 0;
        c.gridwidth = 4;
        centerBox.add(previewImage, c);
        

        add(centerBox, BorderLayout.CENTER);

        pack();
        setSize(500, 350);
        setLocationRelativeTo(parent);
        setVisible(true);
    }

    public void setComponentWidth(JComponent c, int w) {
        Dimension bs = c.getPreferredSize();
        bs.width = w;
        c.setPreferredSize(bs);
        c.setMinimumSize(bs);
        c.setMaximumSize(bs);
    }

    public void updateFontData() {
        loadedFont = null;
        try {
            FileInputStream fis = new FileInputStream(ttfFile);
            loadedFont = Font.createFont(Font.TRUETYPE_FONT, fis);
            fis.close();
        } catch (Exception e) { 
            e.printStackTrace();
            fontNameBox.setText("Error");
            return;
        }

        fontNameBox.setText(loadedFont.getFontName().replace(" ", "") + "20");

        fontSizeBox.setValue(20);
        fontDepthBox.setValue(2);

        renderFontSample();
        infoBox.setText("Estimated " + calculateSize() + " bytes");

    }

    public void renderFontSample() {

        int size = (Integer)fontSizeBox.getValue();
        int depth = (Integer)fontDepthBox.getValue();
        Float fSize = (float)size;
        Font resizedFont = loadedFont.deriveFont(fSize);
        Graphics2D graphic = preview.createGraphics();
        FontRenderContext frc = graphic.getFontRenderContext();
        Rectangle2D bounds = resizedFont.getMaxCharBounds(frc);


        System.err.println(bounds);

        graphic.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_ON);

        graphic.setColor(Color.WHITE);
        graphic.fillRect(0, 0, 450, 80);
        graphic.setColor(Color.BLACK);
        graphic.setFont(resizedFont);

        int maxHeight = (int)Math.ceil(bounds.getHeight());
        int verticalOffset = (int)Math.ceil(0 - bounds.getY());
        int horizontalOffset = (int)Math.ceil(0 - bounds.getX());

        graphic.drawString("0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz", horizontalOffset,  verticalOffset);

        int colors[] = new int[16];

        colors[0] = 0;

        if (depth == 2) {
            colors[1] = 255;
        } else if (depth == 4) {
            colors[1] = 85;
            colors[2] = 170;
            colors[3] = 255;
        } else {
            colors[1] = 17;
            colors[2] = 34;
            colors[3] = 51;
            colors[4] = 68;
            colors[5] = 85;
            colors[6] = 102;
            colors[7] = 199;
            colors[8] = 136;
            colors[9] = 153;
            colors[10] = 170;
            colors[11] = 187;
            colors[12] = 204;
            colors[13] = 221;
            colors[14] = 238;
            colors[15] = 255;
        }

        for (int y = 0; y < 80; y++) {
            for (int x = 0; x < 450; x++) {
                int rgb = preview.getRGB(x, y) & 0xFF;
                int col = rgb / (256/depth);
                Color c = new Color(colors[col], colors[col], colors[col]);
                preview.setRGB(x, y, c.getRGB());
            }
        }

        revalidate();
        previewImage.repaint();
        
    }

    Dimension calculateBoundingSize() {
        BufferedImage workArea = new BufferedImage(500, 500, BufferedImage.TYPE_BYTE_GRAY);

        int size = (Integer)fontSizeBox.getValue();
        int depth = (Integer)fontDepthBox.getValue();
        int first = ((Glyph)firstGlyph.getValue()).getValue();
        int last = ((Glyph)lastGlyph.getValue()).getValue();
        Float fSize = (float)size;

        Font resizedFont = loadedFont.deriveFont(fSize);

        Graphics2D graphic = workArea.createGraphics();
        FontRenderContext frc = graphic.getFontRenderContext();

        int sx = 0;
        int sy = 0;

        for (int glyph = first; glyph <= last; glyph++) {
            char thisChar = (char)glyph;
            String thisString = Character.toString(thisChar);
            Rectangle2D bounds = resizedFont.getStringBounds(thisString, frc);
            int w = (int)Math.ceil(bounds.getWidth());
            int h = (int)Math.ceil(bounds.getHeight());
            if (w > sx) {
                sx = w;
            }
            if (h > sy) {
                sy = h;
            }
        }
        return new Dimension(sx, sy);
    }

    void renderFont() {
        Dimension rect = calculateBoundingSize();
        int size = (Integer)fontSizeBox.getValue();
        Float fSize = (float)size;
        int depth = (Integer)fontDepthBox.getValue();
        int first = ((Glyph)firstGlyph.getValue()).getValue();
        int last = ((Glyph)lastGlyph.getValue()).getValue();
        int bitDepth = 0;
        if (depth == 2) { 
            bitDepth = 1;
        } else if (depth == 4) {
            bitDepth = 2;
        } else if (depth == 16) {
            bitDepth = 4;
        }
        BufferedImage workArea = new BufferedImage((int)rect.getWidth(), (int)rect.getHeight(), BufferedImage.TYPE_BYTE_GRAY);
        Font resizedFont = loadedFont.deriveFont(fSize);
        Graphics2D graphic = workArea.createGraphics();
        graphic.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_ON);
        FontRenderContext frc = graphic.getFontRenderContext();

        int bpl = (int)Math.ceil(rect.getWidth() / 8) * bitDepth;

        ArrayList<DCChar> allChars = new ArrayList<DCChar>();


        for (int glyph = first; glyph <= last; glyph++) {
            graphic.setColor(Color.BLACK);
            graphic.fillRect(0, 0, (int)rect.getWidth(), (int)rect.getHeight());
            graphic.setColor(Color.WHITE);
            graphic.setFont(resizedFont);
            char thisChar = (char)glyph;
            String thisString = Character.toString(thisChar);
            Rectangle2D bounds = resizedFont.getStringBounds(thisString, frc);
            int verticalOffset = (int)Math.ceil(0 - bounds.getY());
            int horizontalOffset = (int)Math.ceil(0 - bounds.getX());
            graphic.drawString(thisString, horizontalOffset,  verticalOffset);
            ArrayList<BigInteger> characterData = new ArrayList<BigInteger>();
            for (int line = 0; line < rect.getHeight(); line++) {
                BigInteger lineData = BigInteger.ZERO;

                for (int pixel = 0; pixel < rect.getWidth(); pixel++) {
                    int rgb = workArea.getRGB(pixel, line) & 0xFF;
                    int col = (rgb / (256/depth));
                    BigInteger thisPixel = BigInteger.valueOf(col);
                    thisPixel = thisPixel.shiftLeft(pixel * bitDepth);
                    lineData = lineData.or(thisPixel);
                }
                characterData.add(lineData);
            }
            DCChar newChar = new DCChar(glyph, (int)bounds.getWidth(), (int)rect.getHeight(), bitDepth, bpl, characterData);
            allChars.add(newChar);
        }   
        DCFont newFont = new DCFont((int)rect.getHeight(), bpl, first, last, bitDepth, fontNameBox.getText(), allChars);
        MainWindow mw = (MainWindow)parent;
        mw.setFont(newFont);
        this.dispose();
    }

    int calculateSize() {
        Dimension rect = calculateBoundingSize();
        int depth = (Integer)fontDepthBox.getValue();
        int first = ((Glyph)firstGlyph.getValue()).getValue();
        int last = ((Glyph)lastGlyph.getValue()).getValue();
        if (depth == 2) { 
            depth = 1;
        } else if (depth == 4) {
            depth = 2;
        } else if (depth == 16) {
            depth = 4;
        }
        int bpl = (int)Math.ceil(rect.getWidth() / 8) * depth;
        System.err.println("Character size: " + rect);
        System.err.println("Bytes per line: " + bpl);
        System.err.println("Lines per character: " + rect.getHeight());
        System.err.println("Bytes per character: " + (bpl * rect.getHeight()));
        System.err.println("Total Bytes: " + ((bpl * rect.getHeight()) * (last - first + 1)));
        return (int)((bpl * rect.getHeight()) * (last - first + 1));
    }
}
