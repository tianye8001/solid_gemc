# eTOF Detector Geometry Structure Analysis

This document provides a detailed breakdown of the **eTOF (endcap Time-of-Flight)** detector geometry structure as defined in [geo.C](file:///home/zwzhao/agy/mrpc/geo.C).

---

## 1. Component Materials and Nominal Dimensions
The table below lists the basic geometry parameters defined in the macro for the individual components of the MRPC (Multi-gap Resistive Plate Chamber) modules.

| Component | Volume Name | Material (Medium) | Thickness (cm) | X-Length (cm) | Y-Width (MRPC1) (cm) | Y-Width (MRPC2) (cm) |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Honeycomb** | `honetcomb_geo` | `honeycomb` | 0.5000 | 50.5 | 58.5 | 31.0 |
| **PCB** | `PCB_geo` | `pcbmvd` (PCB) | 0.0800 | 56.9 | 62.9 | 35.4 |
| **Mylar** | `mylar_geo` | `mylar` | 0.0250 | 50.5 | 58.5 | 31.0 |
| **Electrode** | `electrode_geo` | `carbon` (electrode) | 0.0005 | 48.0 | 56.0 | 28.5 |
| **Outer Glass** | `glass2_geo` | `RPCglass` | 0.0700 | 50.5 | 58.5 | 31.0 |
| **Inner Glass** | `glass1_geo` | `RPCglass` | 0.0500 | 48.0 | 56.0 | 28.5 |
| **Gas Gap** | `gap_geo` | `RPCgas` | 0.0250 | 48.0 | 56.0 | 28.5 |
| **Readout Strip** | `readout_geo` | `copper` | 0.0035 | 48.0 | 1.5 *(per strip)* | 1.5 *(per strip)* |

* **Readout Strip pitch details:** The readout strips are spaced by a strip gap of **0.2 cm** (`width_stripgap`). 
  - **MRPC1** has 32 channels/strips (`n_channel1`).
  - **MRPC2** has 16 channels/strips (`n_channel2`).

---

## 2. Internal Layer Stack-up of a Single MRPC Module (from $-Z$ to $+Z$)
Each MRPC module is a symmetric double-stack Multi-gap Resistive Plate Chamber. The table below outlines the exact stacking order of the 39 layers along the local $Z$-axis (centered around the middle readout strip layer at local $Z = 0$):

> [!NOTE]
> There is a small typo in the analytical `thickness_MRPC` formula in the macro on line 43 (`thickness_glass*8+thickness_innerglass*4` is written, but there are actually **4** outer glasses and **8** inner glasses in the stack). 
> The physical stacking constructed in the code gives a total module thickness of **2.3625 cm** (including the outer honeycomb layers).

| Layer # | Component | Material | Nominal Thickness (cm) | Local $Z$ Range (cm) | Count | Description / Notes |
| :---: | :--- | :--- | :---: | :---: | :---: | :--- |
| **1** | Honeycomb (Bottom) | Honeycomb | 0.5000 | `[-1.18125, -0.68125]` | 1 | Bottom mechanical support |
| **2** | PCB (Bottom Outer) | `pcbmvd` | 0.0800 | `[-0.68125, -0.60125]` | 1 | Outer PCB backplane |
| **3** | Readout Strips (Bottom Outer) | Copper | 0.0035 | `[-0.60125, -0.59775]` | 1 | Bottom readout strip layer |
| **4** | Mylar (Bottom Outer) | Mylar | 0.0250 | `[-0.59775, -0.57275]` | 1 | High-voltage insulating film |
| **5** | Electrode (Bottom Outer) | Carbon | 0.0005 | `[-0.57275, -0.57225]` | 1 | Bottom outer resistive electrode |
| **6** | Outer Glass (Bottom Outer) | Glass | 0.0700 | `[-0.57275, -0.50275]` | 1 | Bounding glass plate (overlaps with thin electrode) |
| **7–15** | Gas Gaps & Inner Glass Plates | Gas / Glass | 0.3250 | `[-0.50275, -0.17725]` | 9 | Bottom active stack: 5 gas gaps (0.025 cm) and 4 floating glasses (0.05 cm) alternating |
| **16** | Outer Glass (Bottom Inner) | Glass | 0.0700 | `[-0.17725, -0.10725]` | 1 | Inner bounding glass plate (bottom stack) |
| **17** | Electrode (Bottom Inner) | Carbon | 0.0005 | `[-0.10725, -0.10675]` | 1 | Inner resistive electrode |
| **18** | Mylar (Bottom Inner) | Mylar | 0.0250 | `[-0.10675, -0.08175]` | 1 | Insulating film |
| **19** | PCB (Bottom Inner) | `pcbmvd` | 0.0800 | `[-0.08175, -0.00175]` | 1 | Inner PCB backplane |
| **20** | **Readout Strips (Central)** | Copper | 0.0035 | `[-0.00175,  0.00175]` | 1 | **Shared central readout strip layer at $Z = 0$** |
| **21** | PCB (Top Inner) | `pcbmvd` | 0.0800 | `[ 0.00175,  0.08175]` | 1 | Inner PCB backplane |
| **22** | Mylar (Top Inner) | Mylar | 0.0250 | `[ 0.08175,  0.10675]` | 1 | Insulating film |
| **23** | Electrode (Top Inner) | Carbon | 0.0005 | `[ 0.10675,  0.10725]` | 1 | Inner resistive electrode |
| **24** | Outer Glass (Top Inner) | Glass | 0.0700 | `[ 0.10725,  0.17725]` | 1 | Inner bounding glass plate (top stack) |
| **25–33** | Gas Gaps & Inner Glass Plates | Gas / Glass | 0.3250 | `[ 0.17725,  0.50275]` | 9 | Top active stack: 5 gas gaps (0.025 cm) and 4 floating glasses (0.05 cm) alternating |
| **34** | Outer Glass (Top Outer) | Glass | 0.0700 | `[ 0.50275,  0.57275]` | 1 | Bounding glass plate |
| **35** | Electrode (Top Outer) | Carbon | 0.0005 | `[ 0.57225,  0.57275]` | 1 | Top outer resistive electrode |
| **36** | Mylar (Top Outer) | Mylar | 0.0250 | `[ 0.57275,  0.59775]` | 1 | High-voltage insulating film |
| **37** | Readout Strips (Top Outer) | Copper | 0.0035 | `[ 0.59775,  0.60125]` | 1 | Top readout strip layer |
| **38** | PCB (Top Outer) | `pcbmvd` | 0.0800 | `[ 0.60125,  0.68125]` | 1 | Outer PCB backplane |
| **39** | Honeycomb (Top) | Honeycomb | 0.5000 | `[ 0.68125,  1.18125]` | 1 | Top mechanical support |

---

## 3. Module Assemblies (`M1`, `M1_1`, `M2`)
Individual MRPC modules are placed inside three distinct assembly configurations (`M1`, `M1_1`, `M2`). This configuration groups modules in the $Y$-direction and shifts them along the local $Z$-axis by $\pm z_{\text{over}}$ (where $z_{\text{over}} \approx 2.22125\text{ cm}$) to overlap them and eliminate dead spaces:

* **Assembly `M1`:** Holds 4 modules:
  * **MRPC1** (Index 0) at $Y = +52.7\text{ cm}, Z = -2.22125\text{ cm}$
  * **MRPC2** (Index 1) at $Y = +12.75\text{ cm}, Z = +2.22125\text{ cm}$
  * **MRPC2** (Index 2) at $Y = -12.75\text{ cm}, Z = -2.22125\text{ cm}$
  * **MRPC1** (Index 3) at $Y = -52.7\text{ cm}, Z = +2.22125\text{ cm}$

* **Assembly `M1_1` (Modified `M1` with shifted central columns):** Holds 4 modules:
  * **MRPC1** (Index 0) at $Y = +52.7\text{ cm}, Z = -2.22125\text{ cm}$
  * **MRPC2** (Index 1) at $Y = +22.75\text{ cm}, Z = +2.22125\text{ cm}$ (shifted by $Y_{\text{mov}} = +10\text{ cm}$)
  * **MRPC2** (Index 2) at $Y = -22.75\text{ cm}, Z = -2.22125\text{ cm}$ (shifted by $Y_{\text{mov}} = -10\text{ cm}$)
  * **MRPC1** (Index 3) at $Y = -52.7\text{ cm}, Z = +2.22125\text{ cm}$

* **Assembly `M2`:** Holds 3 modules:
  * **MRPC1** (Index 0) at $Y = +52.7\text{ cm}, Z = -2.22125\text{ cm}$
  * **MRPC1** (Index 1) at $Y = 0.0\text{ cm}, Z = +2.22125\text{ cm}$
  * **MRPC1** (Index 2) at $Y = -52.7\text{ cm}, Z = -2.22125\text{ cm}$

---

## 4. Endcap (eTOF) System Level Layout
The endcap contains 7 module assemblies arranged along the $X$-axis. Adjacent modules alternate in $Z$ position ($\pm 10\text{ cm}$) to provide overlapping coverage:

* **Reference $Z$ Position ($z_4$):** $246\text{ cm}$

| Assembly Index | Assembly Type | $X$ Center (cm) | $Y$ Center (cm) | $Z$ Center (cm) | $Z$ Range of Assembly (cm) | Position Description |
| :---: | :---: | :---: | :---: | :---: | :---: | :--- |
| **1** | `M2` | `-138.0` | `0.0` | `256.0` | `[252.6, 259.4]` | Far Left |
| **2** | `M2` | `-92.0` | `0.0` | `236.0` | `[232.6, 239.4]` | Outer Left |
| **3** | `M1` | `-46.0` | `0.0` | `256.0` | `[252.6, 259.4]` | Inner Left |
| **4** | `M1_1` | `0.0` | `0.0` | `236.0` | `[232.6, 239.4]` | Center |
| **5** | `M1` | `46.0` | `0.0` | `256.0` | `[252.6, 259.4]` | Inner Right |
| **6** | `M2` | `92.0` | `0.0` | `236.0` | `[232.6, 239.4]` | Outer Right |
| **7** | `M2` | `138.0` | `0.0` | `256.0` | `[252.6, 259.4]` | Far Right |
