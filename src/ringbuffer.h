#ifndef RINGBUFFER_H
#define RINGBUFFER_H


template <typename T>
class RingBuffer
{
public:
    RingBuffer()
    {
        RAW = 0;
    }

    ~RingBuffer()
    {
        if (RAW != 0)
        {
            delete[] RAW;
        }
    }

    void Zero()
    {
        PointerI = 0;
        PointerO = 0;
        Count = 0;
        for (int I = 0; I < Size; I++)
        {
            RAW[I] = 0;
        }
    }

    void ChangeCount(int C)
    {
        if (C > 0)
        {
            Put(C);
            return;
        }
        if (C < 0)
        {
            Get(0 - C);
            return;
        }
    }

    void Clear()
    {
        Get(Count);
    }

    void Init(int S)
    {
        if (RAW != 0)
        {
            delete[] RAW;
        }
        Size = S;
        RAW = new T[S];
        PointerI = 0;
        PointerO = 0;
        Count = 0;
        for (int I = 0; I < Size; I++)
        {
            RAW[I] = 0;
        }
    }

    void Get(int N)
    {
        for (int I = 0; I < N; I++)
        {
            PointerO++;
            if (PointerO == Size)
            {
                PointerO = 0;
            }
            Count--;
        }
    }

    void Get(T * Buf, int N)
    {
        for (int I = 0; I < N; I++)
        {
            Buf[I] = RAW[PointerO];
            PointerO++;
            if (PointerO == Size)
            {
                PointerO = 0;
            }
            Count--;
        }
    }

    void Put(int N, T Val)
    {
        for (int I = 0; I < N; I++)
        {
            RAW[PointerI] = Val;
            PointerI++;
            if (PointerI == Size)
            {
                PointerI = 0;
            }
            Count++;
        }
    }

    void Put(int N)
    {
        T Val = 0;
        if (Count > 0)
        {
            int P = PointerI;
            if (P == 0)
            {
                P = Size;
            }
            P--;
            Val = RAW[P];
        }
        for (int I = 0; I < N; I++)
        {
            RAW[PointerI] = Val;
            PointerI++;
            if (PointerI == Size)
            {
                PointerI = 0;
            }
            Count++;
        }
    }

    void Put(T * Buf, int N)
    {
        for (int I = 0; I < N; I++)
        {
            RAW[PointerI] = Buf[I];
            PointerI++;
            if (PointerI == Size)
            {
                PointerI = 0;
            }
            Count++;
        }
    }

    T GetOne()
    {
        T Val = RAW[PointerO];
        PointerO++;
        if (PointerO == Size)
        {
            PointerO = 0;
        }
        Count--;
        return Val;
    }

    void PutOne(T Val)
    {
        RAW[PointerI] = Val;
        PointerI++;
        if (PointerI == Size)
        {
            PointerI = 0;
        }
        Count++;
    }

    int OverFill()
    {
        int I = 0;
        while (Count >= Size)
        {
            PointerO++;
            if (PointerO == Size)
            {
                PointerO = 0;
            }
            I++;
            Count--;
        }
        return I;
    }

    void First(T * Buf, int N)
    {
        int P = PointerO;
        for (int I = 0; I < N; I++)
        {
            Buf[I] = RAW[P];
            P++;
            if (P == Size)
            {
                P = 0;
            }
        }
    }

    void First(T * Buf, int O, int N)
    {
        int P = PointerO + O;
        while (P >= Size)
        {
            P -= Size;
        }
        for (int I = 0; I < N; I++)
        {
            Buf[I] = RAW[P];
            P++;
            if (P == Size)
            {
                P = 0;
            }
        }
    }

    void Last(T *Buf, int N)
    {
        int P = PointerI - N;
        for (int I = 0; I < N; I++)
        {
            Buf[I] = RAW[P];
            P++;
            if (P == Size)
            {
                P = 0;
            }
        }
    }

    void Last(T *Buf, int O, int N)
    {
        int P = PointerI - N - O;
        while (P < 0)
        {
            P += Size;
        }
        for (int I = 0; I < N; I++)
        {
            Buf[I] = RAW[P];
            P++;
            if (P == Size)
            {
                P = 0;
            }
        }
    }

    int Count;
    int Size;
    T * RAW;
    int PointerI = 0;
    int PointerO = 0;
private:
};

#endif // RINGBUFFER_H
