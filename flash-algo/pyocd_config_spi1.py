from pathlib import Path
import sys

sys.path.append(str(Path(__file__).parent))
import pyocd_shared


"""
Called by pyocd at target connection time.
"""
def will_connect():
    flm = Path(__file__).parent / "STM32G0Bx_SPI1_EEPROM.FLM"
    pyocd_shared.will_connect(flm, target)

"""
Called by pyocd after target connection.
"""
def did_connect():
    pyocd_shared.did_connect(target)
