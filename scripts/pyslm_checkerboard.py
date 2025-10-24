import argparse
import importlib
import json
import os
import sys
from typing import List

import numpy as np


def _import_pyslm():
    try:
        import pyslm  # type: ignore
        return pyslm
    except ImportError:
        script_dir = os.path.dirname(os.path.abspath(__file__))
        candidate_paths = [
            os.path.abspath(os.path.join(script_dir, "..", "pyslm")),
            os.path.abspath(os.path.join(script_dir, "..", "..", "pyslm")),
        ]
        for path in candidate_paths:
            if os.path.isdir(path) and path not in sys.path:
                sys.path.append(path)
        import pyslm  # type: ignore
        return pyslm


def _build_contours(raw_contours: List[List[List[float]]]) -> List[np.ndarray]:
    contours = []
    for contour in raw_contours:
        if len(contour) < 2:
            continue
        contours.append(np.array(contour, dtype=float))
    return contours


def _generate_commands(_pyslm_module, contours: List[np.ndarray], params: dict) -> List[str]:
    if not contours:
        return []

    hatching = importlib.import_module("pyslm.hatching")
    geometry = importlib.import_module("pyslm.geometry")

    hatcher = hatching.IslandHatcher()
    hatcher.hatchDistance = float(params["fill_spacing"])
    hatcher.hatchAngle = float(params["fill_angle_deg"])
    hatcher.layerAngleIncrement = 0.0
    hatcher.islandWidth = float(params["island_width"])
    hatcher.islandOverlap = float(params["island_overlap"])
    hatcher.islandOffset = float(params["island_offset"])
    hatcher.numInnerContours = 0
    hatcher.numOuterContours = 0
    hatcher.spotCompensation = 0.0
    hatcher.contourOffset = 0.0
    hatcher.volumeOffsetHatch = 0.0
    hatcher.hatchSortMethod = hatching.AlternateSort()

    layer = hatcher.hatch(contours)
    if layer is None:
        return []

    commands: List[str] = []
    for layer_geom in layer.geometry:
        if isinstance(layer_geom, geometry.HatchGeometry):
            coords = np.array(layer_geom.coords, dtype=float).reshape(-1, 2)
            for i in range(0, coords.shape[0], 2):
                start = coords[i]
                if i + 1 >= coords.shape[0]:
                    break
                end = coords[i + 1]
                commands.append(f"jump_abs({start[0]:.6f},{start[1]:.6f})")
                commands.append(f"mark_abs({end[0]:.6f},{end[1]:.6f})")
    return commands


def main() -> None:
    parser = argparse.ArgumentParser(description="Generate checkerboard hatch commands using PySLM.")
    parser.add_argument("input_json", help="Path to the input JSON file describing contours and parameters.")
    parser.add_argument("output_txt", help="Path to the output text file where commands will be written.")
    args = parser.parse_args()

    with open(args.input_json, "r", encoding="utf-8-sig") as handle:
        payload = json.load(handle)

    contours = _build_contours(payload.get("contours", []))
    pyslm_module = _import_pyslm()
    commands = _generate_commands(pyslm_module, contours, payload)

    os.makedirs(os.path.dirname(os.path.abspath(args.output_txt)), exist_ok=True)
    with open(args.output_txt, "w", encoding="utf-8") as handle:
        handle.write("\n".join(commands))


if __name__ == "__main__":
    main()
