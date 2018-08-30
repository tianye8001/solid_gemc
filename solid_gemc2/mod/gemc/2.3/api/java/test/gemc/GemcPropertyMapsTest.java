package gemc;

import org.junit.*;
import static org.junit.Assert.*;
import static java.lang.System.out;

import java.lang.UnsupportedOperationException;
import java.util.*;

public class GemcPropertyMapsTest {

    @Test
    public void testConstruction() {
        GemcPropertyMaps data = new GemcPropertyMaps();
    }

    @Test
    public void tesFillDetectors() {
        GemcPropertyMaps data = new GemcPropertyMaps();
        data.put("det0", new GemcDetector());
        data.put("det1", new GemcDetector());

        data.get("det1").put("mother", "det0");

        assertEquals(data.get("det1").get("mother"), "det0");
    }

    @Test
    public void tesFill() {
        GemcPropertyMaps data = new GemcPropertyMaps();
        data.put("detector", new GemcDetector());
        data.put("hit", new GemcHit());
        data.put("bank", new GemcBank());
        data.put("material", new GemcMaterial());
    }

    @Test
    public void testDetectorsToString() {
        GemcPropertyMaps data = new GemcPropertyMaps();
        data.put("det0", new GemcDetector());
        data.put("det1", new GemcDetector());
        String datastr = data.toString();
    }

    public static void main(String args[]) {
        org.junit.runner.JUnitCore.main("gemc.GemcPropertyMapsTest");
    }
}
