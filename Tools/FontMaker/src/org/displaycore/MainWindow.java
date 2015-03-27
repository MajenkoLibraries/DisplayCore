package org.displaycore;

import javax.swing.*;
import javax.swing.filechooser.*;
import javax.swing.border.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

class MainWindow extends JFrame {

    JMenuBar menuBar;
    JMenu fileMenu;
    JMenu MRUMenu;
    JPanel mainPanel;

    JScrollPane characterScroll;
    JPanel characterPanel;
    JPanel editorPanel;
    JScrollPane editorScroll;
    JPanel infoPanel;

    JTextArea fontNameBox;
    JSpinner fontHeightBox;
    JSpinner fontWidthBox;
    JSpinner charWidthBox;
    JSpinner bitDepthBox;

    int pixelZoomSize = 16;

    DCFont loadedFont = null;
    DCChar currentCharacter = null;

    public void open() {
        setResizable(false);
        setLayout(new BorderLayout());
        setTitle("FontMaker for DisplayCore :: No Font");

        menuBar = new JMenuBar();
        fileMenu = new JMenu("File");
        menuBar.add(fileMenu);

        JMenuItem openFont = new JMenuItem("Open font file...");
        openFont.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                openFontFile();
            }
        });
        fileMenu.add(openFont);

        MRUMenu = new JMenu("Recent Fonts");
        fileMenu.add(MRUMenu);
        updateMRU();
        

        add(menuBar, BorderLayout.NORTH);

        mainPanel = new JPanel();
        mainPanel.setLayout(new BorderLayout());

        editorPanel = new JPanel();
        editorScroll = new JScrollPane(editorPanel);
        mainPanel.add(editorScroll, BorderLayout.CENTER);
        infoPanel = new JPanel();
        mainPanel.add(infoPanel, BorderLayout.EAST);

        infoPanel.setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();
        c.gridx = 0;
        c.gridy = 0;
        c.gridwidth = 1;
        c.gridheight = 1;

        fontNameBox = new JTextArea();
        infoPanel.add(new JLabel("Font Name:"), c);
        c.gridx = 1;
        infoPanel.add(fontNameBox, c);
        Dimension bs = fontNameBox.getPreferredSize();
        bs.width = 100;
        fontNameBox.setPreferredSize(bs);
        fontNameBox.setMinimumSize(bs);
        fontNameBox.setMaximumSize(bs);

        c.gridx = 0;
        c.gridy++; 
        infoPanel.add(new JLabel("Font Height:"), c);
        fontHeightBox = new JSpinner();
        c.gridx = 1;
        infoPanel.add(fontHeightBox, c);

        c.gridx = 0;
        c.gridy++; 
        infoPanel.add(new JLabel("Font Width:"), c);
        fontWidthBox = new JSpinner();
        c.gridx = 1;
        infoPanel.add(fontWidthBox, c);

        c.gridx = 0;
        c.gridy++; 
        infoPanel.add(new JLabel("Font Depth:"), c);
        bitDepthBox = new JSpinner();
        c.gridx = 1;
        infoPanel.add(bitDepthBox, c);

        c.gridx = 0;
        c.gridy++; 
        infoPanel.add(new JLabel("Character Width:"), c);
        charWidthBox = new JSpinner();
        c.gridx = 1;
        infoPanel.add(charWidthBox, c);

        charWidthBox.addChangeListener(new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                int cWid = (Integer)charWidthBox.getValue();
                int mWid = (Integer)fontWidthBox.getValue();
                if (cWid > mWid) {
                    charWidthBox.setValue(mWid);
                    cWid = mWid;
                }
                if (currentCharacter != null) {
                    currentCharacter.setWidth(cWid);
                    createEditor(currentCharacter);
                }
            }
        });


        editorPanel.addMouseWheelListener(new MouseWheelListener() {
            public void mouseWheelMoved(MouseWheelEvent e) {
                pixelZoomSize -= e.getWheelRotation();
                if (pixelZoomSize < 4) {
                    pixelZoomSize = 4;
                }
                if (pixelZoomSize > 64) {   
                    pixelZoomSize = 64;
                }

                if (currentCharacter != null) {
                    createEditor(currentCharacter);
                }
            }
        });

        characterPanel = new JPanel();
        characterScroll = new JScrollPane(characterPanel);

        characterPanel.setLayout(new FlowLayout());

        characterScroll.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);
        characterScroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_NEVER);

        populateCharacterScroll();

        mainPanel.add(characterScroll, BorderLayout.SOUTH);

        add(mainPanel, BorderLayout.CENTER);


        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });

        pack();
        setSize(1000, 700);
        setVisible(true);
    }

    void populateCharacterScroll() {
        characterPanel.removeAll();
        if (loadedFont != null) {
            for (int c = loadedFont.startGlyph; c <= loadedFont.endGlyph; c++) {
                for (DCChar ch : loadedFont.characters) {
                    for (MouseListener l : ch.getMouseListeners()) {
                        ch.removeMouseListener(l);
                    }
                    ch.addMouseListener(new MouseListener() {
                        public void mouseEntered(MouseEvent e) {}
                        public void mouseExited(MouseEvent e) {}
                        public void mousePressed(MouseEvent e) {}
                        public void mouseReleased(MouseEvent e) {}
                        public void mouseClicked(MouseEvent e) {
                            DCChar thisChar = (DCChar)(e.getSource());
                            createEditor(thisChar);
                        }
                    });
                    characterPanel.add(ch);
                }
            }
        } else {
            JLabel l = new JLabel("No font loaded");
            characterPanel.add(l);
        }
        revalidate();
    }

    public void openFontFile() {
        JFileChooser fc = new JFileChooser();
        fc.setCurrentDirectory(new File("/u2/home/matt/DC/DisplayCore/Fonts"));
        FileNameExtensionFilter filter = new FileNameExtensionFilter(
            "Font CPP Files", "cpp");
        fc.setFileFilter(filter);
        int rv = fc.showOpenDialog(this);
        if (rv == JFileChooser.APPROVE_OPTION) {
            loadedFont = new DCFont(fc.getSelectedFile());
            addToMRU(fc.getSelectedFile());
            setTitle("FontMaker for DisplayCore :: " + loadedFont.getName());
            updateFontInfo();
            refreshScreen();
        }
    }

    public void refreshScreen() {
        populateCharacterScroll();
    }

    public void createEditor(DCChar thisChar) {

        currentCharacter = thisChar;

        loadedFont.selectGlyph(currentCharacter);
        charWidthBox.setValue(currentCharacter.getWidth());

        editorPanel.removeAll();
        editorPanel.setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();
        int maxCharacterWidth = (loadedFont.bytesPerLine * 8) / loadedFont.bitsPerPixel;

        Dimension pixelSize = new Dimension(pixelZoomSize, pixelZoomSize);

        Border border = BorderFactory.createLineBorder(new Color(128, 128, 128), 1);

        for (int y = 0; y < loadedFont.linesPerCharacter; y++) {
            for (int x = 0; x < maxCharacterWidth; x++) {
                if (x < thisChar.getWidth()) {
                    int col = thisChar.getPixel(x, y);
                    c.gridx = x;
                    c.gridy = y;
                    c.gridwidth = 1;
                    c.gridheight = 1;
                    Pixel l = new Pixel(x, y);
                    int br = 255 - (255 * col / ((1 << loadedFont.bitsPerPixel) - 1));
                    l.setBackground(new Color(br, br, br));
                    l.setBorder(border);
                    l.setOpaque(true);
                    l.setSize(pixelSize);
                    l.setMinimumSize(pixelSize);
                    l.setMaximumSize(pixelSize);
                    l.setPreferredSize(pixelSize);
                    l.addMouseListener(new MouseListener() {
                        public void mouseEntered(MouseEvent e) {
                            Pixel p = (Pixel)(e.getSource());
                            int col = currentCharacter.getPixel(p.getPosition());
                            int maxcol = (1 << loadedFont.bitsPerPixel) - 1;
                            int br;
                            int mods = e.getModifiersEx();
                            if ((mods & MouseEvent.BUTTON1_DOWN_MASK) != 0) {
                                col++; 
                                if (col > maxcol) {
                                    col = maxcol;
                                }
                                currentCharacter.setPixel(p.getPosition(), col);
                                br = 255 - (255 * col / maxcol);
                                p.setBackground(new Color(br, br, br));
                                revalidate();
                            } else if ((mods & MouseEvent.BUTTON3_DOWN_MASK) != 0) {
                                col--;
                                if (col < 0) {
                                    col = 0;
                                }
                                currentCharacter.setPixel(p.getPosition(), col);
                                br = 255 - (255 * col / maxcol);
                                p.setBackground(new Color(br, br, br));
                                revalidate();
                            }
                        }
                        public void mouseExited(MouseEvent e) {}
                        public void mouseClicked(MouseEvent e) {}
                        public void mouseReleased(MouseEvent e) {}
                        public void mousePressed(MouseEvent e) {
                            Pixel p = (Pixel)(e.getSource());
                            int col = currentCharacter.getPixel(p.getPosition());
                            int maxcol = (1 << loadedFont.bitsPerPixel) - 1;
                            int br;
                            switch (e.getButton()) {
                                case MouseEvent.BUTTON1:
                                    col++; 
                                    if (col > maxcol) {
                                        col = maxcol;
                                    }
                                    currentCharacter.setPixel(p.getPosition(), col);
                                    br = 255 - (255 * col / maxcol);
                                    p.setBackground(new Color(br, br, br));
                                    revalidate();
                                    break;
                                case MouseEvent.BUTTON3:
                                    col--;
                                    if (col < 0) {
                                        col = 0;
                                    }
                                    currentCharacter.setPixel(p.getPosition(), col);
                                    br = 255 - (255 * col / maxcol);
                                    p.setBackground(new Color(br, br, br));
                                    revalidate();
                                    break;
                                case MouseEvent.BUTTON2:
                                    break;
                            }
                        }
                    });
                    editorPanel.add(l, c);
                } else {
                    c.gridx = x;
                    c.gridy = y;
                    c.gridwidth = 1;
                    c.gridheight = 1;
                    Pixel l = new Pixel(x, y);
                    l.setBackground(new Color(200, 100, 100));
                    l.setBorder(border);
                    l.setOpaque(true);
                    l.setSize(pixelSize);
                    l.setMinimumSize(pixelSize);
                    l.setMaximumSize(pixelSize);
                    l.setPreferredSize(pixelSize);
                    editorPanel.add(l, c);
                }
            }
        }
        revalidate();
        repaint();
    }

    public void updateMRU() {
        String mru = FontMaker.prefs.get("mru", "");
        String[] mruBits = mru.split("\n");
        MRUMenu.removeAll();
        for (String mb : mruBits) {
            File f = new File(mb);
            if (f.exists()) {
                JMenuItem i = new JMenuItem(f.getName());
                i.setActionCommand(f.getAbsolutePath());
                i.addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent e) {
                        String fn = e.getActionCommand();
                        File f = new File(fn);
                        if (f.exists()) {
                            loadedFont = new DCFont(f);
                            addToMRU(f);
                            setTitle("FontMaker for DisplayCore :: " + loadedFont.getName());
                            updateFontInfo();
                            refreshScreen();
                        }
                    }
                });
                MRUMenu.add(i);
            }
        }
    }

    public void addToMRU(File file) {
        String mru = FontMaker.prefs.get("mru", "");
        String[] mruBits = mru.split("\n");
        int c = 1;
        String out = file.getAbsolutePath();
        for (String mb : mruBits) {
            File f = new File(mb);
            if (f.exists()) {
                if (!(f.getAbsolutePath().equals(file.getAbsolutePath()))) {
                    if (c < 20) {
                        out += "\n";
                        out += f.getAbsolutePath();
                    }
                    c++;
                }
            }
        }
        FontMaker.prefs.put("mru", out);
        updateMRU();
    }

    public void updateFontInfo() {
        fontNameBox.setText(loadedFont.getName());
        fontHeightBox.setValue(loadedFont.getHeight());
        fontWidthBox.setValue(loadedFont.getWidth());
        bitDepthBox.setValue(loadedFont.getDepth());
        charWidthBox.setValue(0);
    }
}
