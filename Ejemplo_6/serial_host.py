import logging
from serial import Serial
import time
import numpy as np
import sklearn.metrics as metrics
import csv

# Logging setup
logging.basicConfig(
    level=logging.DEBUG,  # Change to logging.INFO to reduce verbosity
    format='[%(asctime)s] %(levelname)s: %(message)s',
    datefmt='%H:%M:%S'
)
logger = logging.getLogger(__name__)

PORT = "/dev/ttyUSB1"
BAUDRATE = 9600
STOP_BITS = 1
PARITY = "N"
TEST_LEN = 100
I_FILE = "golden_Inputs.dat"
O_FILE = "hardware_Results.dat"
R_FILE = "golden_Reference.dat"
CSV_FILE = f"results_log.csv"
HEADERS = ["Hardware", "GoldenReference", "AbsoluteError", "PercentualError"]
ABS_TOL = 1
PER_TOL = 10
N = 5

input_data = []
output_data = []
true_data = []

tst_filed = 0

logger.info(f"Opening serial port {PORT} at {BAUDRATE} baud, parity={PARITY}, stopbits={STOP_BITS}.")
serial = Serial(port=PORT, baudrate=BAUDRATE, parity=PARITY, stopbits=STOP_BITS)
logger.info("Listening for board...")

attemps = 0
while (serial.readline().decode('ascii').strip() != "Running! ..."):
    if attemps > 10:
        logger.error("No board detected!")
        serial.close()
        exit()
    attemps += 1
    logger.debug(f"Attempt {attemps}: Waiting for board response...")
    time.sleep(1)

logger.info("Board detected!")

with open(CSV_FILE, 'w', newline='', encoding='UTF8') as csvf:
    with open(I_FILE, "r", encoding="UTF8") as ifile:
        with open(R_FILE, "r", encoding="UTF8") as rfile:
            writer = csv.writer(csvf)
            writer.writerow(HEADERS)

            for rline, tst in zip(rfile, range(TEST_LEN)):
                logger.debug(f"Test ID: {tst}")

                data_in = [float(ifile.readline().strip()) for _ in range(2*N)]
                input_data.append(data_in)

                data_ref = float(rline.strip())
                true_data.append(data_ref)

                for item in data_in:
                    d = (str(item) + "\n").encode("ascii")
                    serial.write(d)
                    logger.debug(f"Sent to device: {item}")
                    time.sleep(0.01)

                logger.debug("Waiting for device response...")
                oline = serial.readline().decode("ascii")
                logger.debug(f"Received line: {oline.strip()}")
                data_out = float(oline.strip().split(":")[1])
                output_data.append(data_out)

                abs_err = abs(data_out - data_ref)
                per_err = 100 * abs_err / (data_out + 1e-16)

                logger.info(
                    f"TEST: {tst}, Expected: {data_ref:.3f}, Got: {data_out:.3f}, "
                    f"AbsErr: {abs_err:.3f}, PerErr: {per_err:.3f}"
                )
                with open(O_FILE, "a", encoding="UTF8") as ofile:
                    ofile.write(
                        f"TEST: {tst},\t Expected: {data_ref:6f} \tGot: {data_out:6f} "
                        f"\t AbsErr: {abs_err:6f} \t PerErr: {per_err:6f} \n"
                    )

                if abs_err > ABS_TOL or per_err > PER_TOL:
                    tst_filed += 1
                    logger.warning(f"TEST {tst} Failed!")

                writer.writerow([data_out, data_ref, abs_err, per_err])

mse = metrics.mean_squared_error(np.array(true_data), np.array(output_data))
mae = metrics.mean_absolute_error(np.array(true_data), np.array(output_data))

logger.info("=" * 60)
logger.info(f"{'Test Summary':^60}")
logger.info("=" * 60)
logger.info(f"{'Total Tests':<30}: {TEST_LEN}")
logger.info(f"{'Failed Tests':<30}: {tst_filed}")
logger.info(f"{'MSE':<30}: {mse:.6f}")
logger.info(f"{'MAE':<30}: {mae:.6f}")
logger.info("=" * 60)

if tst_filed:
    logger.error(f"{'RESULT: FAIL':^60}")
else:
    logger.info(f"{'RESULT: PASS':^60}")
logger.info("=" * 60)
serial.close()
