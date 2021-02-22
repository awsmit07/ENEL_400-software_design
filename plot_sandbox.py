import matplotlib.pyplot as plt
import numpy as np
from pynput import keyboard
import re
import serial
ser = serial.Serial('/dev/tty.usbserial-0001', 9600)
ser.flushInput()
# ser.flushOutput()
data = []
numbers = []


def live_plotter(x_vec, y1_data, line1, identifier='', pause_time=0.066):
    if line1 == []:
        # this is the call to matplotlib that allows dynamic plotting
        plt.ion()
        fig = plt.figure(figsize=(13, 6))
        ax = fig.add_subplot(111)
        # create a variable for the line so we can la111123ter update it
        line1, = ax.plot(x_vec, y1_data, '-o', alpha=0.8)
        # update plot label/title
        plt.ylabel('Y Label')
        plt.title('Title: {}'.format(identifier))
        plt.show()

    # after the figure, axis, and line are created, we only need to update the y-data
    line1.set_ydata(y1_data)
    # adjust limits if new data goes beyond bounds
    if np.min(y1_data) <= line1.axes.get_ylim()[0] or np.max(y1_data) >= line1.axes.get_ylim()[1]:
        plt.ylim([np.min(y1_data) - np.std(y1_data), np.max(y1_data) + np.std(y1_data)])
    # this pauses the data so the figure/axis can catch up - the amount of pause can be altered above
    plt.pause(pause_time)

    # return line so we can update it again in the next iteration
    return line1

size = 100
x_vec = np.linspace(0,1,size+1)[0:-1]
y_vec = np.random.randn(len(x_vec))
line1 = []
x = 0


def on_press(key):
    global y_vec, x_vec, line1
    try:
        print('alphanumeric key {0} pressed'.format(
            key.char))
        if re.match("[0-9]", key.char):
            ""
            y_vec[-1] = int(key.char)/9
            line1 = live_plotter(x_vec, y_vec, line1)
            y_vec = np.append(y_vec[1:], 0.0)
    except AttributeError:
        print('special key {0} pressed'.format(
            key))


def split(word):
    return [char for char in word]


while True:
    # try:
        bytesToRead = ser.inWaiting()

        received = ser.read(bytesToRead).decode('utf-8')
        if received != "":

            if len(received) > 1:
                data.extend(split(received))
                # print(split(received))
            else:
                data.append(received)

            # print(data)
            if len(data) > 20 and data[-1] == " " and data[-2] == " ":
                new_num = int(''.join(data[-7:-2]))
                print(new_num)
                numbers.append(new_num)

                x = x + 1
                # use ggplot style for more sophisticated visuals
                plt.style.use('ggplot')
                # Collect events until released
                # with keyboard.Listener(on_press=on_press) as listener:
                #     listener.join()

                # y_vec[-1] = 3*np.sin(2 * np.pi * x/100)
                y_vec[-1] = new_num

                line1 = live_plotter(x_vec, y_vec, line1)
                y_vec = np.append(y_vec[1:], 0.0)

    # except:
    #     print("Keyboard Interrupt")
    #     break

