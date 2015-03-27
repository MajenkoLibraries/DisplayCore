package org.displaycore;

import javax.swing.UIManager;
import java.util.prefs.*;

class FontMaker {

    public static Preferences prefs;

    public static void main(String[] args) {
        prefs = Preferences.userNodeForPackage(FontMaker.class);
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
        }
        MainWindow mainWindow = new MainWindow();
        mainWindow.open();
    }

}
