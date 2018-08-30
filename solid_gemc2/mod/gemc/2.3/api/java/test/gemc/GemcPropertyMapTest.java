package gemc;

import org.junit.*;
import static org.junit.Assert.*;
import static java.lang.System.out;

import java.lang.UnsupportedOperationException;
import java.util.*;

public class GemcPropertyMapTest {

    @Test
    public void testConstruction() {
        GemcPropertyMap data = new GemcPropertyMap();
    }

    @Test
    public void testSetGet() {
        GemcPropertyMap data = new GemcPropertyMap();
        data.put("key0","value0");
        assertEquals(data.get("key0"), "value0");
    }

    @Test(expected=UnsupportedOperationException.class)
    public void testLock() {
        GemcPropertyMap data = new GemcPropertyMap();
        data.put("key0","value0");
        data.lock();
        assertEquals(data.get("key0"), "value0");
        data.put("key1","value1");
    }

    public static void main(String args[]) {
        org.junit.runner.JUnitCore.main("gemc.GemcPropertyMapTest");
    }
}
