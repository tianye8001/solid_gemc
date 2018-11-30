package gemc;

import org.junit.*;
import static org.junit.Assert.*;
import static java.lang.System.out;

import java.util.*;

public class GemcDetectorTest {

    @Test
    public void testConstruction() {
        GemcDetector data = new GemcDetector();
    }

    @Test
    public void testGet() {
        GemcDetector data = new GemcDetector();
        assertEquals(data.get("mother"),      "root");
        assertEquals(data.get("description"), "");
        assertEquals(data.get("pos"),         "0*cm 0*cm 0*cm");
        assertEquals(data.get("rotation"),    "ordered: zxy 0*deg 0*deg 0*deg");
        assertEquals(data.get("color"),       "808080");
        assertEquals(data.get("type"),        "G4Trap");
        assertEquals(data.get("dimensions"),  "0*cm 0*deg 0*deg 0*cm 0*cm 0*cm 0*deg 0*cm 0*cm 0*cm 0*deg");
        assertEquals(data.get("material"),    "Air");
        assertEquals(data.get("mfield"),      "no");
        assertEquals(data.get("ncopy"),       "1");
        assertEquals(data.get("pMany"),       "1");
        assertEquals(data.get("exist"),       "1");
        assertEquals(data.get("visible"),     "1");
        assertEquals(data.get("style"),       "0");
        assertEquals(data.get("sensitivity"), "no");
        assertEquals(data.get("hit_type"),    "");
        assertEquals(data.get("identifiers"), "");
    }

    @Test
    public void testSet() {
        GemcDetector data = new GemcDetector();
        data.put("mother","another");
        assertEquals(data.get("mother"), "another");
    }

    @Test(expected=UnsupportedOperationException.class)
    public void testLock() {
        GemcDetector data = new GemcDetector();
        data.put("key0","value0");
    }

    @Test
    public void testExample() {
        GemcDetector data = new GemcDetector();

        // Setting parameters
        data.put("mother",      "mother_volume");
        data.put("description", "Description of this detector");
        data.put("pos",         "0*cm 0*cm 0*cm");
        data.put("rotation",    "ordered: zxy 0*deg 0*deg 0*deg");
        data.put("color",       "000050");
        data.put("type",        "G4Trap");
        data.put("dimensions",  "0*cm 0*deg 0*deg 0*cm 0*cm 0*cm 0*deg 0*cm 0*cm 0*cm 0*deg");
        data.put("material",    "Air");
        data.put("mfield",      "no");
        data.put("ncopy",       "1");
        data.put("pMany",       "1");
        data.put("exist",       "1");
        data.put("visible",     "1");
        data.put("style",       "0");
        data.put("sensitivity", "no");
        data.put("hit_type",    "");
        data.put("identifiers", "");

        // creating a string suitable for printing to screen
        String data_str = data.toString();
    }

    public static void main(String args[]) {
        org.junit.runner.JUnitCore.main("gemc.GemcDetectorTest");
    }
}
