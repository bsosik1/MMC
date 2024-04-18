from matplotlib import pyplot as plt
import numpy as np


class Z2_Generator:
    def __init__(self):
        self.is_generated = False
        self.generated = None

    def generate(self, seed, count):
        # Initialization
        self.generated = list()
        prev_x = seed[0]
        prev_y = seed[1]
        prev_z = seed[2]

        # Generation
        for i in range(count):
            x = (171 * prev_x) % 30269
            y = (172 * prev_y) % 30307
            z = (170 * prev_z) % 30323
            k = (x/30269 + y/30307 + z/30323) % 1
            self.generated.append(k)
            prev_x = x
            prev_y = y
            prev_z = z
        self.is_generated = True
        print("Generated successfully!")

    def save_to_file(self, step=1):
        if not self.is_generated:
            print('You need to generate numbers first!')
            return
        # Open file
        filename = f'Z2_generated_step_{step}.txt'
        file = open(filename, 'w')
        # Save to file with given step
        for i in range(len(self.generated) - step):
            line = f'{self.generated[i]} {self.generated[i+step]}\n'
            file.write(line)
        file.close()
        print('Saved successfully!')

    def plot(self, step=1, show_one=False):
        expected_file_name = f'Z2_generated_step_{step}.txt'
        self.save_to_file(step)
        xn, xn_1 = np.loadtxt(expected_file_name, unpack=True)
        plt.figure()
        plt.plot(xn, xn_1, 'ro')
        plt.xlabel('xn')
        plt.title(f'Wykres rozproszenia, krok={step}')
        plt.ylabel(f'xn_{step}')
        plt.grid(linestyle=':')
        if show_one is True:
            plt.show()

def main():
    gen_z2 = Z2_Generator()
    gen_z2.generate([1, 1, 1], 500)
    gen_z2.plot(step=1)
    gen_z2.plot(step=2)
    plt.show()

if __name__ == "__main__":
    main()


