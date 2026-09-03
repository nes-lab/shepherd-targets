# TrafficBench

**NOTE**: this is a stripped copy of <https://github.com/nes-lab/TrafficBench> with small changes (node ID + X, described in readme one dir above).

---

TrafficBench is a tool suite for the experimental exploration of concurrent packet transmissions
and their consequences (physical layer effects) in low-power wireless networks. It integrates
[RSSISpy](https://gitlab.com/nes-lab/rssispy), a software module that enables continuous RSSI
measurements with bit-level time resolution, with a scheduling framework that provides a specialized,
easy-to-use language to implement communication test patterns. The latter offloads the user from
demanding implementation tasks like time-critical interrupt service routines, network bootstrapping,
synchronization, and efficient data logging. Thus, TrafficBench greatly simplifies the experimentation
with different traffic patterns and enables an in-depth inspection of the resulting effects.

TrafficBench consist of two major parts:

* A firmware that runs on the network nodes. Currently, TrafficBench supports Nordic
  Semiconductor [nRF52840](https://www.nordicsemi.com/Products/nRF52840) devices in
  Bluetooth Low Energy (BLE) mode.

* Python scripts that can be used to extract, analyze, and visualize the recorded data.

To learn more about TrafficBench, please read on. You can also have a look at our
[EWSN'22 demo abstract](https://nes-lab.org/wordpress/wp-content/uploads/2022/08/herrmann22trafficbench.pdf)
to gain an impression.

## Installation

In the following we focus on Linux. However, the main host tools are written in Python,
and we use the Python-based [Xonsh](https://xon.sh) shell for helper scripts, so installing
TrafficBench on other platforms should not be a big deal. On Windows, you should make
sure that `*.py` files are started with Python and `*.xsh` files with Xonsh, respectively.
You can also use the [Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/about).

Installation steps:

1. Install [SEGGER Embedded Studio for ARM](https://www.segger.com/downloads/embedded-studio/#ESforARM) (SES).[^fn-ses]
   In our tests we have used SES version V6.34.
   You do not need the nRF Connect SDK.
   Depending on your test environment, you may need the
   [nRF Command Line Tools](https://www.nordicsemi.com/Products/Development-tools/nrf-command-line-tools)
   to program the target devices.

2. Set up a [Python 3](https://www.python.org/) environment (we have used Python 3.8 for our tests).
   We recommend to use a Python virtual environment, which can be
   created with `python3 -m venv <name_of_virtualenv>`
   and activated with `source <path_to_virtualenv>/bin/activate`.

3. Create a project directory and clone this repository into it:
   `git clone https://gitlab.com/nes-lab/trafficbench.git`.

4. Go to subfolder `host` and install all required Python modules:
   `pip install -r requirements.txt`.

After these steps, you should be able to start SES (start menu), Xonsh (`xonsh`),
ViTables (`vitables`), and Glue (`glue.xsh` in the `host` subfolder).

[^fn-ses]: SES is free for Nordic customers,
  see [news @ Segger](https://www.segger.com/news/segger-embedded-studio-ide-now-free-for-nordic-sdk-users/)
  and [tools-info @ nordic](https://www.nordicsemi.com/Products/Development-tools/Segger-Embedded-Studio).

## Usage

### Firmware

The task of the TrafficBench firmware is to implement a user-defined communication schedule
and to log all related data (events, transmitted and received packets, RSSI data streams, etc.)
to the UART terminal. Here, "implement" means to do everything that is needed to realize the
schedule, i.e., network wake-up, clock and state synchronization, and schedule program execution.

The firmware is ready to use in the sense that providing the schedule of interest (formulated
in the specialized language, see below) is enough
to be able to compile and run the firmware with the specific schedule.
To demonstrate the process, the source code comes with a tutorial schedule that can be used
to test the tool chain and run a simple test on a few Nordic
[nRF52840 DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK)
development boards forming a small wireless network (using three boards is perfect, but even
a single board is enough to test the tool chain).
To do so, use the following steps:

1. Start SES and open the project [`target/nrf52840/project_ses/TrafficBench.emProject`](target/nrf52840/project_ses/TrafficBench.emProject).

2. Make sure to select "Release" as the active configuration (do not use "Release_FlockLab").
   Compile the project and program the executable into all boards.

3. For each board: Open a terminal (UART settings 230400,8,N,1, hardware flow control enabled).
   Press the reset button on the board and test if you see some output at the terminal.

   In case of problems, temporarily disable hardware flow control by setting
   `GPI_ARM_NRF_STDOUT_UART_FLOWCONTROL_MODE` to 0 in [`config.h`](target/nrf52840/project_ses/config.h)
   and try again. If hardware flow control is the reason for problems, then re-enable it and find out
   how to configure the terminal correctly (e.g. with PuTTY you can use -sercfg "230400,8,n,1,D").
   *Do not run the firmware without flow control on nRF52840 DK boards* because this can lead to
   awkward data losses.

4. You will be asked for a node ID at each terminal. Provide a unique ID for each board starting from 1, 2, ...

   The ID is stored in the device's UICR area, so it is kept persistent and not asked for again
   (also after re-programming). If you want to set a new ID, keep Button 1 pressed during boot-up,
   which enforces the ID prompt. See [`main.c`](target/nrf52840/main.c) for the details.

5. When everything is set up, press Button 1 at node 1. This starts communication and generates
   output at all terminals.

To evaluate the data with the TrafficBench host tools, you need to log the UART output of each
node to one or more files (e.g. one file per node). We do not provide any scripts for this task
because the right way to do it depends on your setup and the used terminal program (e.g. with
PuTTY you can use the command line option `-log <filename>`).
Public testbeds like [FlockLab](https://www.flocklab.ethz.ch) do it automatically (if UART
logging is turned on in the test configuration).

## Research

TrafficBench has been developed in the [Networked Embedded Systems Lab](https://nes-lab.org)
at [TU Dresden](https://tu-dresden.de) and [University of Freiburg](https://uni-freiburg.de/en/).
Please visit <https://nes-lab.org> to find out more.

---
