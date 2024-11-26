using System;
using System.Collections.Generic;
using System.Threading;

class Program
{
    private static readonly object lockObject = new object(); // Объект для синхронизации

    static void Main(string[] args)
    {
        int mem = 0; //  оценка 
        List<Big> lbig = new List<Big>(1000);

     
        Thread fillerThread = new Thread(() =>
        {
            Random random = new Random();
            while (true)
            {
                lock (lockObject)
                {
                    foreach (var big in lbig)
                    {
                       
                        for (int i = 0; i < big.IntArray.Length; i++)
                        {
                            big.IntArray[i] = random.Next();
                        }
                    }
                }
                Thread.Sleep(1000); 
            }
        });
        fillerThread.IsBackground = true;
        fillerThread.Start();

      
        while (true)
        {
            lock (lockObject)
            {
                lbig.Add(new Big());
            }
            mem += 1048576 * 128; 
            Console.WriteLine("{0,-6} MB allocated", (mem / 1048576));
            Thread.Sleep(5000);
        }
    }
}

class Big
{
    public Int32[] IntArray;
    public Big()
    {
        IntArray = new int[1048576 * 32]; // Массив размером 128 MB
    }
}
