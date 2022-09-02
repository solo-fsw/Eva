
def init_serial_device(com_port, baudrate=115200, timeout=2):
    # Initializes the serial port: configure port and open port.

    # Input: com port address (e.g. COM4), baudrate, timeout
    # Output: a serial device

    # NOTE: when the com_port is FAKECOM, a FakeSerial object is created and returned.
    # NOTE: when communication with the serial device fails, the output is a string with an error message

    import serial

    # When the com port address is FAKECOM a FakeSerial object is created.
    if com_port == 'FAKECOM':

        class FakeSerial:
            def __init__(self):
                self.port = com_port

        ser = FakeSerial()

    else:

        # Create serial device
        ser = serial.Serial()

        try:
            # Configure port
            ser.port = com_port
            ser.baudrate = baudrate
            ser.bytesize = 8
            ser.parity = 'N'
            ser.stopbits = 1

            ser.timeout = timeout

            # Open serial device
            ser.open()

        # Capture serial communication error
        except serial.serialutil.SerialException:
            ser.close()
            ser = 'ERROR: could not open serial device'

    return ser


def close_serial_device(ser):
    # Closes the serial device
    # Input: the serial device

    ser.close()


def init_eva(com_port):
    # Opens eva in data mode (if eva is already open, make sure to close before opening!):
    # Input: com port address (e.g. COM4)

    # Todo: check for eva:

    ser = init_serial_device(com_port)
    return ser


def data_mode(ser):
    # Puts eva into data mode
    # Input: the serial device (eva)
    # Output: the serial device (eva; in data mode)

    # Close eva:
    close_eva(ser)

    # Open eva in data mode:
    ser = init_serial_device(ser.port)
    return ser


def command_mode(ser):
    # Puts eva into command mode
    # Input: the serial device (eva)
    # Output: the serial device (eva; in command mode)

    # Close eva:
    close_eva(ser)

    # Open eva in command mode:
    ser = init_serial_device(ser.port, 4800)
    print(ser)
    return ser


def close_eva(ser):
    # Closes eva
    # Input: the serial device (eva)

    if not ser.port == 'FAKECOM':
        close_serial_device(ser)


def write_marker(ser, marker):
    # Send marker to eva
    # Input: the serial device (eva), marker value (has to be an int)

    if ser.port == 'FAKECOM':
        print('could not send marker because fake EVA is used')
    else:
        # Make sure the marker is an int, only ints can be sent to eva
        if type(marker) == int:
            ser.write(bytearray([marker]))
        else:
            print('could not send marker that is not int')


def command(ser, cmd):
    # Send command to eva
    # Input: the serial device (eva), the command (has to be str)
    # Output: the reply of eva

    import time

    if ser.port == 'FAKECOM':
        return 'ERROR: no data, FAKECOM used.'

    else:
        # Make sure eva is set to command mode (baudrate = 4800)
        if not ser.baudrate == 4800:
            return 'ERROR, eva not in command mode'

        else:
            # Command should be string
            if type(cmd) == str:

                import json

                def is_json(myjson):
                    try:
                        json_object = json.loads(myjson)
                    except ValueError as e:
                        return False
                    return True

                # Send command
                ser.flushInput()
                ser.write(cmd.encode())
                time.sleep(0.1)

                # Get reply
                data = ser.readline()
                decoded_data = data.decode('utf-8')

                # If reply is json string, decode it for easier processing
                if is_json(decoded_data):
                    decoded_data = json.loads(decoded_data)

                # Return the data
                return decoded_data

            else:
                return 'ERROR: no data, command should be string'


def get_device(ser):
    # Get device name

    response = command(ser, 'V')

    if type(response) == dict:
        device = response.get('Device')
        return device
    else:
        return response


def get_mode(ser):
    # Get mode (active or passive)

    mode = command(ser, 'M')
    return mode


def get_serial(ser):
    # Get serial number

    response = command(ser, 'V')

    if type(response) == dict:
        serial = response.get('Serialno')
        return serial
    else:
        return response


def get_version(ser):
    # Get version

    response = command(ser, 'V')

    if type(response) == dict:
        version = response.get('Version')
        return version
    else:
        return response


def get_my_info(ser):
    # Get all information

    my_info = command(ser, 'V')
    return my_info


def ping(ser):
    # ping eva

    ping_answer = command(ser, 'P')
    return ping_answer


def set_active_mode(ser):
    # Set into active mode

    active_mode = command(ser, 'A')
    return active_mode


def set_passive_mode(ser):
    # Set into passive mode

    passive_mode = command(ser, 'S')
    return passive_mode


# # The code below is example code of how to use the functions in this module:
# import time
#
# # Initialize eva with correct com port (eva is put into data mode by default).
# # The com port can be found in the Device Manager.
# eva = init_eva('COM7')
#
# # Send marker value:
# write_marker(eva, 255)
# time.sleep(1)
# write_marker(eva, 0)
#
# # Put eva into command mode:
# eva = command_mode(eva)
#
# # Get information from eva:
# eva_device = get_device(eva)
# eva_mode = get_mode(eva)
# eva_serial = get_serial(eva)
# eva_version = get_version(eva)
# eva_info = get_my_info(eva)
# eva_ping = ping(eva)
# eva_passive_mode = set_passive_mode(eva)
# eva_active_mode = set_active_mode(eva)
#
# # Put eva back into data mode:
# eva = data_mode(eva)
#
# # Reset markers
# write_marker(eva, 0)
# time.sleep(1)
#
#
#
# # Print the information:
# print(eva)
# print('eva_port: ' + eva.port)
# print('eva_device: ' + eva_device)
# print('eva_mode: ' + eva_mode)
# print('eva_serial: ' + eva_serial)
# print('eva_version: ' + eva_version)
# print(eva_info)
# print('eva_ping: ' + eva_ping)
# print('eva_passive_mode: ' + eva_passive_mode)
# print('eva_active_mode: ' + eva_active_mode)
#
# # Close eva:
# close_eva(eva)

