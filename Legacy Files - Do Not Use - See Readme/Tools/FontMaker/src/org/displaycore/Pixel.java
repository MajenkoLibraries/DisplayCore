package org.displaycore;

import javax.swing.*;
import java.awt.*;

public class Pixel extends JLabel {
    Point myLoc;

    public Pixel(int x, int y) {
        myLoc = new Point(x, y);
    }

    public Point getPosition() {
        return myLoc;
    }
}
