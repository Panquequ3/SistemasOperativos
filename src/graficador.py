import matplotlib.pyplot as plt
import sys

def dataExtract(data_path):
    dic = {}
    with open(data_path,'w') as data:
        content = data.readlines()
        for lines in content:
            temp = lines.strip().split(";")
            if(temp[0] not in dic):
                dic[temp[0]] = []
            dic[temp[0]].append(float(temp[1]))
    return dic


def main():
    if len(sys.argv)!=4:
        print("F")
        return 0
    data_path = sys.argv[1]
    graphic_path = sys.argv[2]
    repeats = int(sys.argv[3])
    
    x = range(1,repeats+1)    
    dic = dataExtract(data_path)
    for key in dic.keys():
       keyLabel = key + " Hilos"
       plt.plot(x,dic[key],label=keylabel)

    plt.title('Gráfico de Líneas con Múltiples Series')
    plt.xlabel('Repeticiones')
    plt.ylabel('Tiempo')
    plt.legend()
    
    plt.savefig(graphic_path)
    
    return 0
    
    
if __name__ == "__main__":
    main()