
import gemc.*
import static java.lang.System.out

def detectors = new GemcPropertyMaps()

def det0 = new GemcDetector()
det0.put("mother","root")
det0.put("color","404040")

detectors.put("det0", det0)

def det1 = new GemcDetector()
det1.put("mother", "det0")
det1.put("color", "ae2312")

detectors.put("det1", det1)

out.print(detectors.toPaddedString()+"\n")


