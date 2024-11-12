#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <cmath> 

using namespace std;

#pragma pack(push, 1)

enum Speciality { ITIS, ME, KN, FI, TN };
string speciality_str[] = { "Інформатика ",
                            "Математика та економіка", "Комп'ютерні науки",
                            "Фізика та інформатика", "Трудове навчання" };

struct Students
{
    string surname;
    int course;
    Speciality speciality;
    int grade_physics;
    int grade_math;
    union
    {
        int grade_nm;
        int grade_program;
        int grade_ped;
    };
};

#pragma pack(pop)

void Create(Students* S, const int N);
double student_avarage_evaluation(Students* S, const int i);
void Print(Students* S, const int N);
void p_sort(Students* S, int N);
int* i_sort(Students* S, const int N);
void i_print(Students* S, int* I, const int N);
bool b_search(Students* S, const int N, const string surname, const int course, const double avarage_evaluation);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість студентів: "; cin >> N;

    Students* S = new Students[N];

    string f_surname;
    double f_avarage_evaluation;
    int f_course;

    int MenuItem;

    while (true)
    {
        cout << endl << endl << endl;
        cout << "Оберіть дію:" << endl;
        cout << "1 - Ввести інформацію про студентів" << endl;
        cout << "2 - Вивести інформацію про студентів" << endl;
        cout << "3 - Фізично впорядкувати інформацію" << endl;
        cout << "4 - Індексно впорядкувати інформацію" << endl;
        cout << "5 - Бінарний пошук студента" << endl;
        cout << "0 - Завершити роботу програми" << endl;
        cout << "Введіть: "; cin >> MenuItem; cout << endl;

        switch (MenuItem)
        {
        case 1:
            Create(S, N);
            break;
        case 2:
            Print(S, N);
            break;
        case 3:
            p_sort(S, N);
            Print(S, N);
            break;
        case 4:
            i_print(S, i_sort(S, N), N);
            break;
        case 5:
            cout << "Введіть критерії пошуку: " << endl;
            cout << "Прізвище: ";
            cin.ignore();
            getline(cin, f_surname);
            cout << endl;

            do
            {
                cout << "Курс: ";
                cin >> f_course;
                cout << endl;
            } while (f_course < 1 || f_course > 6);

            do
            {
                cout << "Середній бал: ";
                cin >> f_avarage_evaluation;
                cout << endl;
            } while (f_avarage_evaluation < 1 || f_avarage_evaluation > 5);

            if (b_search(S, N, f_surname, f_course, f_avarage_evaluation))
            {
                cout << "Студент знайдений" << endl;
            }
            else
            {
                cout << "Студент не знайдений" << endl;
            }
            break;
        }

        if (MenuItem == 0) break;
    }

    delete[] S;
    return 0;
}

void Create(Students* S, const int N)
{
    for (int i = 0; i < N; i++)
    {
        int speciality;
        cout << "Номер студента: " << i + 1 << endl;
        cin.ignore();
        cout << "Прізвище: "; getline(cin, S[i].surname); cout << endl;

        do
        {
            cout << "Курс: "; cin >> S[i].course; cout << endl;
        } while (S[i].course < 1 || S[i].course > 6);

        do
        {
            cout << "Спеціальність(0 - Інформатика, 1 - Математика та економіка, 2 - Комп'ютерні науки,";
            cout << "\n3 - Фізика та інформатика, 4 - Трудове навчання): ";
            cin >> speciality;
            S[i].speciality = (Speciality)speciality;
        } while (S[i].speciality < 0 || S[i].speciality > 4);

        do
        {
            cout << "Оцінка з фізики: "; cin >> S[i].grade_physics; cout << endl;
        } while (S[i].grade_physics < 1 || S[i].grade_physics > 5);


        do
        {
            cout << "Оцінка з математики: "; cin >> S[i].grade_math; cout << endl;
        } while (S[i].grade_math < 1 || S[i].grade_math > 5);

        switch (S[i].speciality)
        {
        case KN:
            do
            {
                cout << "Оцінка з програмування: "; cin >> S[i].grade_program; cout << endl;
            } while (S[i].grade_program < 1 || S[i].grade_program > 5);
            break;

        case ITIS:
            do
            {
                cout << "Оцінка з чисельних методів: "; cin >> S[i].grade_nm; cout << endl;
            } while (S[i].grade_nm < 1 || S[i].grade_nm > 5);
            break;

        default:
            do
            {
                cout << "Оцінка з педагогіки: "; cin >> S[i].grade_ped; cout << endl;
            } while (S[i].grade_ped < 1 || S[i].grade_ped > 5);
        }
        cout << endl;
    }
}

void Print(Students* S, const int N)
{
    cout << "======================================================================================================================================" << endl;
    cout << "|  №  |   Прізвище   | Курс |      Спеціальність      |  Фізика  |  Математика  |  Програмування  |  Чисельні методи  |  Педагогіка  |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << S[i].surname
            << "| " << setw(4) << right << S[i].course << " "
            << "| " << setw(24) << left << speciality_str[S[i].speciality]
            << "|  " << setw(7) << right << S[i].grade_physics << " "
            << "|  " << setw(11) << right << S[i].grade_math << " ";

        switch (S[i].speciality)
        {
        case KN:
            cout << "|" << setw(9) << S[i].grade_program << setw(9);
            cout << "|" << setw(9) << "-" << setw(11);
            cout << "|" << setw(8) << "-" << setw(7) << "|";
            break;
        case ITIS:
            cout << "|" << setw(9) << "-" << setw(9);
            cout << "|" << setw(9) << S[i].grade_nm << setw(11);
            cout << "|" << setw(8) << "-" << setw(7) << "|";
            break;
        default:
            cout << "|" << setw(9) << "-" << setw(9);
            cout << "|" << setw(9) << "-" << setw(11);
            cout << "|" << setw(8) << S[i].grade_ped << setw(7) << "|";
            break;
        }

        cout << endl << "--------------------------------------------------------------------------------------------------------------------------------------" << endl;
    }
}

double student_avarage_evaluation(Students* S, const int i)
{
    double average = (S[i].grade_physics + S[i].grade_math);

    switch (S[i].speciality)
    {
    case KN:
        average += S[i].grade_program;
        break;
    case ITIS:
        average += S[i].grade_nm;
        break;
    case FI:
    case TN:
        average += S[i].grade_ped;
        break;
    }

    return average / (2 + (S[i].speciality == KN) + (S[i].speciality == ITIS) + (S[i].speciality == FI) + (S[i].speciality == TN));
}

void p_sort(Students* S, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (student_avarage_evaluation(S, i) < student_avarage_evaluation(S, j) ||
                (fabs(student_avarage_evaluation(S, i) - student_avarage_evaluation(S, j)) < 1e-6 && S[i].course > S[j].course) ||
                (fabs(student_avarage_evaluation(S, i) - student_avarage_evaluation(S, j)) < 1e-6 && S[i].course == S[j].course && S[i].surname < S[j].surname))
            {
                swap(S[i], S[j]);
            }
        }
    }
}

int* i_sort(Students* S, const int N)
{
    int* I = new int[N];

    for (int i = 0; i < N; i++)
    {
        I[i] = i;
    }


    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (student_avarage_evaluation(S, I[i]) < student_avarage_evaluation(S, I[j]) ||
                (fabs(student_avarage_evaluation(S, I[i]) - student_avarage_evaluation(S, I[j])) < 1e-6 && S[I[i]].course > S[I[j]].course) ||
                (fabs(student_avarage_evaluation(S, I[i]) - student_avarage_evaluation(S, I[j])) < 1e-6 && S[I[i]].course == S[I[j]].course && S[I[i]].surname < S[I[j]].surname))
            {
                swap(I[i], I[j]);
            }
        }
    }

    return I;
}

void i_print(Students* S, int* I, const int N)
{
    cout << "======================================================================================================================================" << endl;
    cout << "|  №  |   Прізвище   | Курс |      Спеціальність      |  Фізика  |  Математика  |  Програмування  |  Чисельні методи  |  Педагогіка  |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(13) << left << S[I[i]].surname
            << "| " << setw(4) << right << S[I[i]].course << " "
            << "| " << setw(24) << left << speciality_str[S[I[i]].speciality]
            << "|  " << setw(7) << right << S[I[i]].grade_physics << " "
            << "|  " << setw(11) << right << S[I[i]].grade_math << " ";

        switch (S[I[i]].speciality)
        {
        case KN:
            cout << "|" << setw(9) << S[I[i]].grade_program << setw(9);
            cout << "|" << setw(9) << "-" << setw(11);
            cout << "|" << setw(8) << "-" << setw(7) << "|";
            break;
        case ITIS:
            cout << "|" << setw(9) << "-" << setw(9);
            cout << "|" << setw(9) << S[I[i]].grade_nm << setw(11);
            cout << "|" << setw(8) << "-" << setw(7) << "|";
            break;
        default:
            cout << "|" << setw(9) << "-" << setw(9);
            cout << "|" << setw(9) << "-" << setw(11);
            cout << "|" << setw(8) << S[I[i]].grade_ped << setw(7) << "|";
            break;
        }

        cout << endl << "--------------------------------------------------------------------------------------------------------------------------------------" << endl;
    }
}

bool b_search(Students* S, const int N, const string surname, const int course, const double average_evaluation) {
    int left = 0;
    int right = N - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        double current_average = student_avarage_evaluation(S, mid);

        cout << "Перевірка: " << S[mid].surname << ", курс: " << S[mid].course
            << ", середній бал: " << current_average << endl;

        if (S[mid].surname < surname ||
            (S[mid].surname == surname && S[mid].course < course) ||
            (S[mid].surname == surname && S[mid].course == course && current_average < average_evaluation)) {
            left = mid + 1;
        }
        else if (S[mid].surname > surname ||
            (S[mid].surname == surname && S[mid].course > course) ||
            (S[mid].surname == surname && S[mid].course == course && current_average > average_evaluation)) {
            right = mid - 1;
        }
        else {
            return true;
        }
    }

    return false;
}
