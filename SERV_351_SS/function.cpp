#include "function.h"
#include <QString>
#include <QStringList>

QByteArray parse(QString msg,int position){
    QStringList bufer = msg.split(" ");
    if(bufer[0] == "reg"){
        bufer.removeFirst();
        return sign_up(bufer).toUtf8();
    }
    else if(bufer[0] == "auth"){
        bufer.removeFirst();
        bufer.append(" "+ QString::number(position));
        return sign_in(bufer).toUtf8();
    }
    else if(bufer[0] == "point"){
        bufer.removeFirst();
        return get_point(bufer).toUtf8();
    }
    else if(bufer[0] == "get"){
        bufer.removeFirst();
        return get_tack(bufer).toUtf8();
    }
    else if(bufer[0]=="ans"){
        bufer.removeFirst();
        if (bufer[0]==bufer[1]){
            bufer.removeFirst();
            bufer.removeFirst();
            bufer[1]="+1";
            task_toBD(bufer);
            return bufer[1].toUtf8();
        }
        else{
            bufer.removeFirst();
            bufer.removeFirst();
            bufer[1]="-1";
            task_toBD(bufer);
            return bufer[1].toUtf8();
        }

    }
    //ans2 otvet right_size task2 -/+1 log
    else if(bufer[0]=="ans2" ){
        bufer.removeFirst();
        int a= bufer[0].size()/2;
        if(dolgrap(bufer[0]) and bufer[0].size()/2==bufer[1].toInt()){            
            bufer.removeFirst();
            bufer.removeFirst();
            bufer[1]="+1";
            task_toBD(bufer);
            return bufer[1].toUtf8();
        }
        else{
            bufer.removeFirst();
            bufer.removeFirst();
            bufer[1]="-1";
            task_toBD(bufer);
            return bufer[1].toUtf8();
        }
    }
    /*else if(bufer[0]=="dis")
    {
        bufer.removeFirst();
        dis(bufer);
    }*/
    bufer.clear();
}
/*
void dis(QStringList temp)
{
    QStringList Ubdate = singletonBD::getInstance()->getValue("UPDATE User set Unique_Num = null where login = "+ temp[0]);
    if(Ubdate.size()>0) qDebug()<<"Ne good";
}*/

QString get_point(QStringList temp){
    QStringList ans = singletonBD::getInstance()->getValue("Select "+ temp[0] +" from User where Login = '" + temp[1]+"'");
    return ans[0];
}

QString sign_in(QStringList temp){
    QStringList ans = singletonBD::getInstance()->getValue("select Login, Password from User where Login = '" + temp[0] + "' and Password= '"+ temp[1]+"'");
    //здесь у нас отправляется запрос на БД с проверкой существования пользователя
    if(ans.size()>0 && ans[0]!="eror"){//если хоть что-то пришло значит "гуд"
        QStringList Ubdate = singletonBD::getInstance()->getValue("UPDATE User set Unique_Num = "+temp[2]+" where Login = '"+ temp[0]+"'");
        return "auth&+";
        }
    else    return "auth&-";
}

QString sign_up(QStringList temp) {
    QStringList ans = singletonBD::getInstance()->getValue("INSERT INTO User(Login, Password, Mail, task1, task2, task3, task4) VALUES ('" + temp[0] + "','" + temp[1] + "','" + temp[2] + "',0,0,0,0)");
    if(ans.size()>0)//если пришла ошибка, то не гуд
        return "reg&-";
    else    return "reg&+";
}

void task_toBD(QStringList temp){
    QString water;
    water.append("UPDATE User set "+temp[0]+" = "+temp[0]+" "+temp[1]+ " where Login = '"+ temp[2]+"'");
    QStringList ans = singletonBD::getInstance()->getValue(water);
}





void randvec(std::vector<std::vector<int>>& g, int n, int m) {
    //n, m размер матрицы, колво x y вершин
    int k; //случайное число для заполнения матрицы
    int f; //случайнок кол-во соединений от вершины
    //n = rand() % 10 + 1; m = rand() % 10 + 1;
    /*vector<vector<int>> g(n);*/
    for (int i = 0; i < n; i++) {
        f = rand() % (m + 1);
        int p = m; //кол=во элементов в векторе с доступными вершинами
        std::vector<int> nums; //вектор
        for (int o = 0; o < p; o++) { //заполнение этого вектора
            nums.push_back(o);
        }

        for (int j = 0; j < f; j++) {
            k = rand() % p;
            g[i].push_back(nums[k]);
            p--;
            nums.erase(nums.begin() + k);
        }
    }

}



bool try_kuhn(int v, std::vector<char>& used, std::vector<int>& mt, std::vector<std::vector<int>>& g) {

    if (used[v])  return false;
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (mt[to] == -1 || try_kuhn(mt[to], used, mt, g)) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}


int fun()
{
    return rand() % 100 + 1;
}

bool dolgrap(QString answer) {
    int len_ans = answer.length();//длина строки
    std::set<QString> chet;//значения вершин х
    std::set<QString> nechet;//значения вершин y
    int n = 0;
    if (len_ans % 2 == 0) {//если все по парам, то может быть паросочетаниями
        for (auto a : answer) {
            if (n % 2 == 0) {//для различия заполнения x и y
                chet.insert(a);
            }
            else {
                nechet.insert(a);
            }
            n++;
        }
        int pol_ans = len_ans / 2;//если не совпадали и это паросочетания,
        //то должно быть по половине строки
        if (chet.size() == pol_ans and nechet.size() == pol_ans) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

QString get_tack(QStringList temp)
{
    QString ans;
    if(temp[0]=="task1")
    {

        const int SIZE = 9;
        int a[SIZE][SIZE]; // матрица связей
        int d[SIZE]; // минимальное расстояние
        int v[SIZE]; // посещенные вершины
        int temp, minindex, min;
        int begin_index = rand() % 9 + 1 - 1; //индекс начальной вершины, вершина - 1
        int end = rand() % 9 + 1 - 1; // индекс конечной вершины, вершиина - 1
        // Инициализация матрицы связей
        for (int i = 0; i < SIZE; i++)
                        {
                            a[i][i] = 0;
                            for (int j = i + 1; j < SIZE; j++) {

                                if ((i + 1) == 1) {
                                    if ((j + 1) == 2 or (j + 1) == 8 or (j + 1) == 9) {
                                        temp = fun();
                                        a[i][j] = temp;
                                        a[j][i] = temp;
                                    }
                                    else if ((j + 1) == 7) {
                                        a[i][j] = fun();
                                        a[j][i] = 0;
                                    }
                                    else {
                                        temp = 0;
                                        a[i][j] = temp;
                                        a[j][i] = temp;
                                    }
                                }
                                else if ((i + 1) == 2) {
                                    if ((j + 1) == 3 or (j + 1) == 7 or (j + 1) == 9) {
                                        temp = fun();
                                        a[i][j] = temp;
                                        a[j][i] = temp;
                                    }
                                    else {
                                        temp = 0;
                                        a[i][j] = temp;
                                        a[j][i] = temp;
                                    }
                                }
                                else if ((i + 1) == 3) {
                                    if ((j + 1) == 4 or (j + 1) == 6 or (j + 1) == 9) {
                                        temp = fun();
                                        a[i][j] = temp;
                                        a[j][i] = temp;
                                    }
                                    else {
                                        temp = 0;
                                        a[i][j] = temp;
                                        a[j][i] = temp;
                                    }
                                }
                                else if ((i + 1) == 4) {
                                    if ((j + 1) == 7) {
                                        temp = fun();
                                        a[i][j] = temp;
                                        a[j][i] = temp;
                                    }
                                    else if ((j + 1) == 5 or (j + 1) == 6) {
                                        a[i][j] = fun();
                                        a[j][i] = 0;
                                    }
                                    else {
                                        temp = 0;
                                        a[i][j] = temp;
                                        a[j][i] = temp;
                                    }
                                }
                                else if ((i + 1) == 5) {
                                    if ((j + 1) == 6) {
                                        temp = fun();
                                        a[i][j] = temp;
                                        a[j][i] = temp;
                                    }
                                    else {
                                        temp = 0;
                                        a[i][j] = temp;
                                        a[j][i] = temp;
                                    }
                                }
                                else if ((i + 1) == 6) {
                                    if ((j + 1) == 7 or (j + 1) == 8 or (j + 1) == 9) {
                                        temp = fun();
                                        a[i][j] = temp;
                                        a[j][i] = temp;
                                    }
                                    else {
                                        temp = 0;
                                        a[i][j] = temp;
                                        a[j][i] = temp;
                                    }
                                }
                                else if ((i + 1) == 7) {
                                    if ((j + 1) == 9) {
                                        temp = fun();
                                        a[i][j] = temp;
                                        a[j][i] = temp;
                                    }
                                    else {
                                        temp = 0;
                                        a[i][j] = temp;
                                        a[j][i] = temp;
                                    }
                                }
                                else {
                                    if ((j + 1) == 9) {
                                        temp = fun();
                                        a[i][j] = temp;
                                        a[j][i] = temp;
                                    }
                                    else {
                                        temp = 0;
                                        a[i][j] = temp;
                                        a[j][i] = temp;
                                    }
                                }
                            }
                        }
        ans.append("Найти кратчайший пути от вершины " + QString::number(begin_index + 1) + " до вершины " + QString::number(end + 1) + "\nМатрица смежностей:\n");
        // Вывод матрицы связей
                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++) {
                        ans.append(QString::number(a[i][j]) + "  ");
                    }
                    ans.append("\n");
                }
                //Инициализация вершин и расстояний
                               for (int i = 0; i < SIZE; i++)
                               {
                                   d[i] = 10000;
                                   v[i] = 1;
                               }
                               d[begin_index] = 0;
                                   // Шаг алгоритма
                                   do {
                                       minindex = 10000;
                                       min = 10000;
                                       for (int i = 0; i < SIZE; i++)
                                       { // Если вершину ещё не обошли и вес меньше min
                                           if ((v[i] == 1) && (d[i] < min))
                                           { // Переприсваиваем значения
                                               min = d[i];
                                               minindex = i;
                                           }
                                       }
                                       // Добавляем найденный минимальный вес
                                       // к текущему весу вершины
                                       // и сравниваем с текущим минимальным весом вершины
                                       if (minindex != 10000)
                                       {
                                           for (int i = 0; i < SIZE; i++)
                                           {
                                               if (a[minindex][i] > 0)
                                               {
                                                   temp = min + a[minindex][i];
                                                   if (temp < d[i])
                                                   {
                                                       d[i] = temp;
                                                   }
                                               }
                                           }
                                           v[minindex] = 0;
                                       }
                                   } while (minindex < 10000);

                                   // Восстановление пути
                                   int ver[SIZE]; // массив посещенных вершин
                                   ver[0] = end + 1; // начальный элемент - конечная вершина
                                   int k = 1; // индекс предыдущей вершины
                                   int weight = d[end]; // вес конечной вершины

                                   while (end != begin_index) // пока не дошли до начальной вершины
                                   {
                                       for (int i = 0; i < SIZE; i++) // просматриваем все вершины
                                           if (a[i][end] != 0)   // если связь есть
                                           {
                                               int temp = weight - a[i][end]; // определяем вес пути из предыдущей вершины
                                               if (temp == d[i]) // если вес совпал с рассчитанным
                                               {                 // значит из этой вершины и был переход
                                                   weight = temp; // сохраняем новый вес
                                                   end = i;       // сохраняем предыдущую вершину
                                                   ver[k] = i + 1; // и записываем ее в массив
                                                   k++;
                                               }
                                           }
                                   }
        ans.append("||");
        QString st = "";
        //std::cout << "\nВывод кратчайшего пути\n";
        for (int i = k - 1; i >= 0; i--)
        {
            st.append(QString::number((ver[i])));
        }
        //cout << st << '\n';

        ans.append(st);
        return ans;

    }
    else if(temp[0]=="task2")
    {
        int n, k;
            n = rand() % 9 + 1;
            k = rand() % 9 + 1;
            std::vector < std::vector<int> > g(n);
            std::vector<int> mt;
            std::vector<char> used;
            std::vector<int> nums;
            randvec(g, n, k);
            ans.append("Матрица смежностей: \n");
            for (int i = 0; i < n; i++) {
                if (g[i].empty()) {
                    ans.append("- \n");
                }
                else {
                    for (auto j : g[i]) {
                        ans.append(QString::number(j + 1)+ " ");
                    }
                    ans.append("\n");
                }
            }
            ans.append("\n");

            mt.assign(k, -1);
            std::vector<char> used1(n);
            for (int i = 0; i < n; ++i)
                for (size_t j = 0; j < g[i].size(); ++j)
                    if (mt[g[i][j]] == -1) {
                        mt[g[i][j]] = i;
                        used1[i] = true;
                        break;
                    }
            for (int i = 0; i < n; ++i) {
                if (used1[i])  continue;
                used.assign(n, false);
                try_kuhn(i, used, mt, g);
            }
            int maxi = 0; //длина максимального паросочетания
            for (int i = 0; i < k; ++i) //потом удалить
                if (mt[i] != -1) {
                   maxi++;
                }
            ans.append("||");
            ans.append(QString::number(maxi));
            return ans;
    }
    else if(temp[0]=="task3")
    {

    }
}




