import matplotlib.pyplot as plt
import sys

def dataExtract(datos):
    dick = {}
    with open(datos,'w') as data:
        contenido = data.readlines()
        for linea in contenido:
            temp = linea.strip().split(";")
            if(temp[0] not in dick):
                dick[temp[0]] = []
            dick[temp[0]].append(float(temp[1]))
    return dick

def main():
    #if len(sys.argv)!=4:
    #    return 0
    
    #datos = sys.argv[1]
    #path = sys.argv[2]
    #repeticiones = sys.argv[3]
    
    x = range(1,6)
    
    #x = range(1,repeticiones+1)
    
    #dic = dataExtract(datos)
    #for key in dic.keys():
    #   keyLabel = key + " Hilos"
    #   plt.plot(x,dic[key],label=keylabel)
    y1 = [2, 3, 5, 7, 11]
    y2 = [1, 4, 6,8, 10]

    plt.plot(x, y1, label='Serie 1')
    plt.plot(x, y2, label='Serie 2')

    plt.title('Gráfico de Líneas con Múltiples Series')
    plt.xlabel('Repeticiones')
    plt.ylabel('Tiempo')
    plt.legend()
    
    plt.show()
    
    #
    return 0
    
    
if __name__ == "__main__":
    main()