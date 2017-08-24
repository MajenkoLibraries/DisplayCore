package org.displaycore;

import javax.swing.*;
import javax.swing.border.*;
import javax.swing.event.*;
import javax.imageio.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import javax.swing.filechooser.*;
import java.awt.image.*;
import java.awt.font.*;
import java.awt.geom.*;
import java.math.*;

public class BitmapParser extends JDialog {

    static File lastOpenLocation;

    JFrame parent;
    JTextArea fontNameBox;
    Font loadedFont;
    File bmpFile;
    JSpinner firstGlyph;
    JSpinner lastGlyph;
    JSpinner topGutter;
    JSpinner leftGutter;
    JSpinner charsPerLine;
    JSpinner rightMargin;
    JSpinner bottomMargin;
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

    public BitmapParser(JFrame p) {
        super(p, JDialog.ModalityType.APPLICATION_MODAL);
        parent = p;
        glyphList = new Glyph[256];
        for (int i = 0; i < 256; i++) {
            glyphList[i] = new Glyph(i);
        }
    }

    public void open() {
        setTitle("Parse Bitmap Font");
        setLayout(new BorderLayout());

        JPanel buttonBox = new JPanel();
        buttonBox.setLayout(new FlowLayout(FlowLayout.RIGHT));

        infoBox = new JLabel();
        buttonBox.add(infoBox);
        
        JButton cancelButton = new JButton("Cancel");
        cancelButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                BitmapParser.this.dispose();
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
                    "Bitmap Files", "png");
                fc.setFileFilter(filter);
                int rv = fc.showOpenDialog(BitmapParser.this);
                if (rv == JFileChooser.APPROVE_OPTION) {
                    bmpFile = fc.getSelectedFile();
                    lastOpenLocation = bmpFile.getParentFile();
                    updateFontData();
                }
            }
        });
        centerBox.add(selectFileButton, c);

        c.gridy++;

        c.gridx = 0;
        c.weightx = 0D;
        c.gridwidth = 1;
        centerBox.add(new JLabel("Top Gutter: "), c);
        c.gridx = 1;
        c.gridwidth = 3;
        c.weightx = 1D;

        topGutter = new JSpinner();
        topGutter.setValue(0);
        centerBox.add(topGutter, c);

        topGutter.addChangeListener(new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                renderFontSample();
            }
        });

        c.gridy++;

        c.gridx = 0;
        c.weightx = 0D;
        c.gridwidth = 1;
        centerBox.add(new JLabel("Left Gutter: "), c);
        c.gridx = 1;
        c.gridwidth = 3;
        c.weightx = 1D;
        leftGutter = new JSpinner();
        leftGutter.setValue(0);
        centerBox.add(leftGutter, c);

        leftGutter.addChangeListener(new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                renderFontSample();
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
//                infoBox.setText("Estimated " + calculateSize() + " bytes");
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
//                infoBox.setText("Estimated " + calculateSize() + " bytes");
            }
        });

        preview = new BufferedImage(256, 256, BufferedImage.TYPE_INT_RGB);
        previewImage = new JLabel(new ImageIcon(preview));

        c.gridy++;
        c.gridx = 0;
        c.gridwidth = 4;
        centerBox.add(previewImage, c);
        

        add(centerBox, BorderLayout.CENTER);

        pack();
        setSize(500, 700);
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

        renderFontSample();

    }

    public void renderFontSample() {

        try {
            preview = ImageIO.read(bmpFile);
            previewImage.setIcon(new ImageIcon(preview));
        } catch (Exception e) {
        }

        int colors[] = new int[2];

        colors[0] = 0;
        colors[1] = 255;

        for (int y = 0; y < preview.getHeight(); y++) {
            for (int x = 0; x < preview.getWidth(); x++) {
                int rgb = preview.getRGB(x, y) & 0xFF;
                int col = (rgb >> 7) & 0x01;
                Color c = new Color(colors[col], colors[col], colors[col]);
                preview.setRGB(x, y, c.getRGB());
            }
        }

        int tg = (Integer)topGutter.getValue();
        int lg = (Integer)leftGutter.getValue();

        if (tg > 0) {
            for (int x = 0; x < preview.getWidth(); x++) {
                for (int y = 0; y < tg; y++) {
                    int rgb = preview.getRGB(x, y) & 0xFF;
                    int col = (rgb >> 7) & 0x01;
                    Color c = new Color(colors[col], 0, 0);
                    preview.setRGB(x, y, c.getRGB());
                }
            }
        }

        if (lg > 0) {
            for (int y = 0; y < preview.getHeight(); y++) {
                for (int x = 0; x < lg; x++) {
                    int rgb = preview.getRGB(x, y) & 0xFF;
                    int col = (rgb >> 7) & 0x01;
                    Color c = new Color(colors[col], 0, 0);
                    preview.setRGB(x, y, c.getRGB());
                }
            }
        }

        revalidate();
        previewImage.repaint();
        
    }

    void renderFont() {
        this.dispose();
    }

    int calculateSize() {
        return 0;
    }
}
