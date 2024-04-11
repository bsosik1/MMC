from matplotlib import pyplot as plt
import numpy as np
import os.path


class Z1_Generator:
    def __init__(self, a, m, c=0):
        self.a = a
        self.m = m
        self.c = c
        self.is_generated = False
        self.generated = None

    def generate(self, seed, count):
        # Initialization
        self.generated = list()
        prev = seed
        self.generated.append(prev)
        # Generation
        for i in range(count):
            next = (self.a * prev + self.c) % self.m
            self.generated.append(next)
            prev = next
        self.is_generated = True
        print("Generated successfully!")

    def save_to_file(self, step=1):
        if not self.is_generated:
            print('You need to generate numbers first!')
            return
        # Open file
        filename = f'generated_step_{step}_a_{self.a}.txt'
        file = open(filename, 'w')
        # Save to file with given step
        for i in range(len(self.generated) - step):
            line = f'{self.generated[i]} {self.generated[i+step]}\n'
            file.write(line)
        file.close()
        print('Saved successfully!')

    def plot(self, step=1, show_one=False):
        expected_file_name = f'generated_step_{step}_a_{self.a}.txt'
        self.save_to_file(step)
        xn, xn_1 = np.loadtxt(expected_file_name, unpack=True)
        plt.figure()
        plt.plot(xn, xn_1, 'ro')
        plt.xlabel('xn')
        plt.title(f'Wykres rozproszenia, a={self.a}, krok={step}')
        plt.ylabel(f'xn_{step}')
        plt.grid(linestyle=':')
        if show_one is True:
            plt.show()

    def plot_autocorr(self):
        data = np.array(self.generated, dtype=np.float32)
        plt.figure()
        plt.title(f'Autocorrelation for a={self.a}')
        plt.xlabel('Lags')
        max = len(self.generated) - 1
        plt.acorr(data, maxlags=max)
        plt.grid(linestyle=':')

def main():
    gen_17 = Z1_Generator(a=17, m=(pow(2, 13)-1))
    gen_17.generate(1, 2500)
    gen_17.plot(step=1)
    gen_17.plot(step=2)
    gen_17.plot_autocorr()

    gen_85 = Z1_Generator(a=85, m=(pow(2, 13)-1))
    gen_85.generate(1, 2500)
    gen_85.plot(step=1)
    gen_85.plot(step=2)
    gen_85.plot_autocorr()

    plt.show()

if __name__ == "__main__":
    main()


