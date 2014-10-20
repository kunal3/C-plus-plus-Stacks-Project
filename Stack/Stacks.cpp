
//            Kunal Agrawal
//               STACKS

//++++++++++  Library Calls  +++++++++++++++++

#include <stdlib.h>
#include <iostream.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <strings.h>
#include <termios.h>
#include <unistd.h>
#include<iomanip.h>

using namespace std;

//================= Prototypes  =================

void gotoxy(int, int);
void clrscr (void);
int getch();

void fifo(int, int [], int);
void mru(int, int [], int);
void lru(int, int [], int);
void opt(int, int [], int);
bool on_shelf(int, int [], int);


//+++++++++++++++++ Main   ++++++++++++++++++++
int main ()
{
    int limit1=0,limit2=0,j=0;
    int a1[30],a2[30];
    int counter1=0,counter2=0;

    for(int i=0;i<30;i++)
    {
        a1[i]=0;
        a2[i]=0;
    }
    a1[0]=a2[0]=1;

    //  Inputing first list of books and its limit
    cout<<"Give me the limit for first list: ";
    cin>>limit1;
    cout<<"\nEnter the first list of books: ";
    while(a1[j]!=0)
    {
        j++;
        cin>>a1[j];
    }
    for(int i=0;i<29;i++)
        a1[i]=a1[i+1];

    for(int j=0;j<29;j++)
        if(a1[j]!=0)
            counter1++;

//      Inputing second list of books and its limit
    j=0;
    cout<<"\nGive me the limit for second list: ";
    cin>>limit2;
    cout<<"\nEnter the second list of books: ";
    while(a2[j]!=0)
    {
        j++;
        cin>>a2[j];
    }
    for(int i=0;i<29;i++)
        a2[i]=a2[i+1];

    for(int j=0;j<29;j++)
        if(a2[j]!=0)
            counter2++;
    
    // Calling all the functions
    cout<<"\nOutputs-";
    fifo(limit1, a1, counter1);
    lru(limit1, a1, counter1);
    mru(limit1, a1, counter1);
    opt(limit1, a1, counter1);
    fifo(limit2, a2, counter2);
    lru(limit2, a2, counter2);
    mru(limit2, a2, counter2);
    opt(limit2, a2, counter2);

    cout<<"\n\n\n";
    return (1);
}

// +++++++++++++++***** FIFO  ****++++++++++++++++++++++++++++++
void fifo(int size, int list[],int num)
{
    int shelf[size];
    int counter=0;
    int shelf_counter=1;

    shelf[0]=list[0];
    
    //  Arranging the first "shelf" number of books
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
            if(list[i]==shelf[j])
                counter++;

        //  If the book isn't already in the shelf
        if(counter==0)
        {
            shelf[shelf_counter]=list[i];
            shelf_counter++;
        }
        // Resetting the shelf_counter when it reaches the last shelf
        if(shelf_counter==size)
            shelf_counter=0;
        counter=0;
    }

    //  Arranging the remaining books
    for(int i=size;i<num;i++)
    {
        for(int j=0;j<size;j++)
            if(list[i]==shelf[j])
                counter++;

        //  If the book isn't already in the shelf
        if(counter==0)
        {
            shelf[shelf_counter]=list[i];
            shelf_counter++;
        }
        // Resetting the shelf_counter when it reaches the last shelf
        if(shelf_counter==size)
            shelf_counter=0;
        counter=0;
    }
    // Printing the final shelf
    cout<<"\n";
    for(int i=0;i<size;i++)
        cout<<shelf[i]<<" ";
}

// +++++++++++++++++ On shelf ++++++++++++++++++++++++++++
bool on_shelf(int book, int shelf[], int size)
{
    // A function to check whether a book is already on the shelf
    bool answer=false;
    for(int i=0; i<size; i++)
        if(shelf[i]==book)
             answer=true;
    return answer;
}

// +++++++++++++**** LRU ****++++++++++++++++++++++++++++++++
void lru(int size, int list[],int num)
{
    int shelf[size];
    int use[size];
    int counter=0;
    int pos=0;
    int n=size;
    int count=0;
    
    for(int i=0;i<size;i++)
    {
        shelf[i]=0;
        use[i]=0;
    }
    // For the first "shelf" number of books
    for(int i=0;i<n;i++)
    {
        // Checks if the books is alread on the shelf using on_shelf function
        if(on_shelf(list[i], shelf, size))
        {
            n++;
            counter++;
        }
        else    // If the books ins't on one of the shelves
        {
            if(counter==0)
                shelf[i]=list[i];
            if(counter>0)
            {
                use[i]=1;
                shelf[i-1]=list[i];
            }
            counter=0;
        }
        // Keeping track of the number of times a book has consecutively stayed in the shelf
        for(int j=0;j<size;j++)
            if(shelf[j]!=0)
                use[j]++;
    }
    // For the remaining books
    for(int i=n;i<num;i++)
    {
        // Checking if the book is already on the shelf
        for(int j=0;j<size;j++)
            if(list[i]==shelf[j])
            {
                counter++;
                count=j;
            }
        // If the isn't already on the shelf
        if(counter==0)
        {
            pos=0;
            for(int k=1;k<size;k++)
                if(use[k]>use[pos])
                    pos=k;
            shelf[pos]=list[i];     // Replacing the book which was most consecutively used
            use[pos]=1;
            for(int j=0;j<size;j++)
                if(j!=pos)
                    use[j]++;
        }
        if(counter>0)   // If the book is already on the shelf
        {
            use[count]=1;
            for(int j=0;j<size;j++)
                if(j!=count)
                    use[j]++;
        }
        counter=0;
    }
    // Printing the final shelf
    cout<<endl;
    for(int k=0;k<size;k++)
        cout<<shelf[k]<<" ";
}

// +++++++++++++**** MRU *****+++++++++++++++++++++++++++++
void mru(int size, int list[],int num)
{
    int shelf[size];
    int counter=0;
    int mru=0;

    // Making every shelf 0
    for(int i=0;i<size;i++)
        shelf[i]=0;

    // For the first "shelf" number of books
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
            if(list[i]==shelf[j])
                counter++;
        // If the book isn't on any of the shelves
        if(counter==0)
        {
            shelf[i]=list[i];
            mru=list[i];
        }
        // If the book is on any of the shelves
        if(counter>0)
            mru=0;
        counter=0;
    }
    // For the remaining inputs
    for(int i=size;i<num;i++)
    {
        for(int k=0;k<size;k++)
            if(list[i]==shelf[k])
                counter++;
        // If the book isn't on any of the shelves
        if(counter==0)
        {
            for(int l=0;l<size;l++)
                if(shelf[l]==mru)
                    shelf[l]=list[i];
            mru=list[i];
        }
        // If the book is on any of the shelves
        if(counter>0)
            mru=list[i];
        counter=0;
    }
    // Printing the final shelf
    cout<<"\n";
    for(int i=0;i<size;i++)
        cout<<shelf[i]<<" ";
}

// +++++++++++++**** OPT ****+++++++++++++++++++++++++++++++++
void opt(int size, int list[],int num)
{
    int shelf[size];
    int dist[size];
    int use[size];
    int counter=0;
    int pos=0;
    int n=size;
    int match=0;

    // Making the use, shelf and distance array 0
    for(int i=0;i<size;i++)
    {
        use[i]=0;
        shelf[i]=0;
    }
    for(int i=0;i<num;i++)
        dist[i]=0;

    // For the first "shelf" number of books
    for(int i=0;i<n;i++)
    {
        // Checks if the books is alread on the shelf using on_shelf function
        if(on_shelf(list[i], shelf, size))
        {
            n++;
            counter++;
        }
        else    // If the books ins't on one of the shelves
        {
            if(counter==0)
                shelf[i]=list[i];
            if(counter>0)
                shelf[i-1]=list[i];
            counter=0;
        }
        // Keeping track of the number of times a book has consecutively stayed in the shelf
        for(int j=0;j<size;j++)
            if(shelf[j]!=0)
                use[j]++;
    }
    // For the remainging books
    for(int i=n;i<num;i++)
    {
        // Chechks if the book is already on the shelf
        for(int k=0;k<size;k++)
            if(list[i]==shelf[k])
                match++;
        // If it isn't, goes in here
        if(match==0)
        {
            // Keeping track of when a book will be used next
            for(int j=0;j<size;j++)
                for(int k=i;k<num;k++)
                {
                    if(shelf[j]!=list[k])
                        dist[j]++;
                    else
                        k=num;
                }

            //Checks if more than one books are used for the same number of times
            for(int m=0;m<size;m++)
                for(int n=0;n<size;n++)
                    if(dist[m]==dist[n])
                        counter++;
            // If more than one books are NOT used for the same number of times
            if(counter==size)
            {
                // Calculate the position of the book which is not needed for the longest period of time
                for(int k=1;k<size;k++)
                    if(dist[k]>dist[pos])
                        pos=k;
                shelf[pos]=list[i];
                // Keeping track of the number of times a book has consecutively stayed in the shelf
                use[pos]=1;
                for(int j=0;j<size;j++)
                    if(j!=pos)
                        use[j]++;
            }
            pos=0;
            // If more than one book will not be used for longest period of time
            if(counter>size)
            {
                // Calculating the book which was on shelf for most consecutive days
                for(int k=1;k<size;k++)
                    if(use[k]>use[pos])
                        pos=k;
                shelf[pos]=list[i];
                use[pos]=1;
            }
            counter=0;
            pos=0;
            match=0;
        }  // End of if(match==0)
        for(int m=0;m<size;m++)
            dist[m]=0;
        match=0;
    }
    // Printing final shelf
    cout<<endl;
    for(int i=0;i<size;i++)
        cout<<shelf[i]<<" ";

}

// +++++++++++++   GoToXY     ++++++++++++++++++++++++++++++++

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//+++++++++++++++  Clrscr    ++++++++++++++++++++++++++++++++++

void clrscr(void)
{
  static HANDLE hStdout = NULL;
  static CONSOLE_SCREEN_BUFFER_INFO csbi;
  const COORD startCoords = {0,0};
  DWORD dummy;

  if(!hStdout)
  {
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hStdout,&csbi);
  }

  FillConsoleOutputCharacter(hStdout,
                             ' ',
                             csbi.dwSize.X * csbi.dwSize.Y,
                             startCoords,
                             &dummy);
  gotoxy(0,0);

}
//++++++++++++++++  Getch    ++++++++++++++++++++++++++++++++

int getch()
 {

    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}
   