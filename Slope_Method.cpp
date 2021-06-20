#include <bits/stdc++.h>
#include <math.h>

using namespace std;

#define N 10000 // Total Number of points in textfile.txt, dont change it!

float *get_my_file() // Function to read textfile.txt
{
    float *a;
    a = new float[N];
    fstream newfile;
    newfile.open("testfile.txt", ios::in);

    if (newfile.is_open())
    {
        string tp;
        int i = 0;
        while (getline(newfile, tp))
        {
            a[i] = stof(tp);
            i++;
        }
        newfile.close();
    }
    else
    {
        cout << "File not read!!\n";
    }

    return a;
}

float findMean(float a[], int n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum = sum + a[i];
    }
    return sum / n;
}

float findStd(float a[], int n)
{
    float m = findMean(a, n);
    float s = 0;
    for (int i = 0; i < n; i++)
    {
        s += (a[i] - m) * (a[i] - m);
    }
    s = s / (n - 1);
    s = sqrt(s);
    return s;
}

int main()
{
    float *input = get_my_file();
    // Uncomment the code below to check if the file is successfully printed to the console
    auto temp = input;
    vector<float> value;
    for (int i = 0; i < N; i++)
    {
        // cout<<*temp<<endl;
        value.push_back(*temp);
        temp++;
    }

    float slope[9999];
    for (int i = 1; i < 10000; i++)
    {
        slope[i - 1] = value[i] - value[i - 1];
    }
    float mean = findMean(slope, 9999);
    float sd = findStd(slope, 9999);
    vector<int> anomalyindex;
    int k = 0;
    for (int i = 0; i < 9999; i++)
    {
        if (slope[i] > mean + (3.5 * sd) || slope[i] < mean - (3.5 * sd))
        {
            k++;
            if (k == 1)
            {
                anomalyindex.push_back(i + 1);
            }
            else
            {
                anomalyindex.push_back(i + 2);
            }
            i = i + 3;
        }
    }
    cout << "Outlier values with Index " << endl
         << "Index\t\t"
         << "Value" << endl;
    for (int i = 0; i < k; i++)
    {
        cout << anomalyindex[i] << "\t\t" << value[anomalyindex[i] - 1] << endl;
    }
}