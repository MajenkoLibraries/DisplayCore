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

public class TrueTypeRender extends JDialog {

    JFrame parent;
    JTextArea fontNameBox;
    Font loadedFont;
    File ttfFile;
    JSpinner fontSizeBox;
    JSpinner fontDepthBox;
    BufferedImage preview;
    JLabel previewImage;

    public TrueTypeRender(JFrame p) {
        super(p, JDialog.ModalityType.APPLICATION_MODAL);
        parent = p;
    }

    public void open() {
        setTitle("Render TrueType Font");
        setLayout(new BorderLayout());

        JPanel buttonBox = new JPanel();
        buttonBox.setLayout(new FlowLayout(FlowLayout.RIGHT));
        
        JButton cancelButton = new JButton("Cancel");
        cancelButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                TrueTypeRender.this.dispose();
            }
        });
        buttonBox.add(cancelButton);

        JButton importButton = new JButton("Render Font");
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
                fc.setCurrentDirectory(new File("/usr/share/fonts/truetype"));
                FileNameExtensionFilter filter = new FileNameExtensionFilter(
                    "TrueType Font Files", "ttf");
                fc.setFileFilter(filter);
                int rv = fc.showOpenDialog(TrueTypeRender.this);
                if (rv == JFileChooser.APPROVE_OPTION) {
                    ttfFile = fc.getSelectedFile();
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

        Integer[] validSizes = {
            6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
            31, 32, 33, 34, 35, 36, 37, 38, 39, 40 };
        SpinnerListModel sizeModel = new SpinnerListModel(Arrays.asList(validSizes));
        fontSizeBox = new JSpinner(sizeModel);
        fontSizeBox.setValue(20);
        centerBox.add(fontSizeBox, c);

        fontSizeBox.addChangeListener(new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                renderFontSample();
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

        Integer[] validColors = { 2, 4, 8 };
        SpinnerListModel depthModel = new SpinnerListModel(Arrays.asList(validColors));
        fontDepthBox = new JSpinner(depthModel);
        fontDepthBox.setValue(2);
        centerBox.add(fontDepthBox, c);

        fontDepthBox.addChangeListener(new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                renderFontSample();
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
        setSize(500, 300);
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

        fontNameBox.setText(loadedFont.getFontName().replace(" ", ""));

        fontSizeBox.setValue(20);
        fontDepthBox.setValue(2);

        renderFontSample();

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

        int maxHeight = (int)bounds.getHeight() - (int)bounds.getY();

        graphic.drawString("AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz", 10, maxHeight);

        int colors[] = new int[8];

        colors[0] = 0;

        if (depth == 2) {
            colors[1] = 255;
        } else if (depth == 4) {
            colors[1] = 85;
            colors[2] = 170;
            colors[3] = 255;
        } else {
            colors[1] = 36;
            colors[2] = 72;
            colors[3] = 108;
            colors[4] = 144;
            colors[5] = 180;
            colors[6] = 216;
            colors[7] = 255;
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

}
