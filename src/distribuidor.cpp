vector<string> split_(string line){
    //lista de los elementos ya separados
    //su forma es {id, operacion, num1, num2}
    vector<string>list; 

    string aux = "";
    int i = 0;

    // almacenamos el id
    while(line[i] != ';')
        i++;
    list.push_back(line.substr(0,i));
    line = line.substr(i+1); //borramos hasta el ; restante
    aux = "";

    // almacenamos la operacion
    while(line[i] != ';'){
        aux = aux + line[i];
        i++;
    }
    list.push_back(aux);

    //tomamos la parte que queremos procesar, añadimos una ',' para procesar los numeros
    line = line.substr(i+1) + ",";
    aux = ""; 

    // almacenamos los numeros
    for(char c : line){
        if(c != ',')
            aux = aux + c;
        else{
            list.push_back(aux); //los añadimos a la lista
            aux = "";
        }
    }
    return list; 
}
//probando push