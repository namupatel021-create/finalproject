
#include <iostream>
#include <vector>
using namespace std;

class Node{
public:
    int id;
    string name;
    int marks;
    Node *next;

    Node(int i,string n,int m){
        id=i;
        name=n;
        marks=m;
        next=NULL;
    }
};

class LinkedList{
    Node *head;
public:
    LinkedList(){ head=NULL; }

    void addStudent(int id,string name,int marks){
        Node *newNode=new Node(id,name,marks);
        if(head==NULL){ head=newNode; return; }

        Node *temp=head;
        while(temp->next!=NULL) temp=temp->next;
        temp->next=newNode;
    }

    void display(){
        Node *temp=head;
        cout<<"\nID\tName\tMarks\n";
        while(temp){
            cout<<temp->id<<"\t"<<temp->name<<"\t"<<temp->marks<<endl;
            temp=temp->next;
        }
    }

    void deleteStudent(int id){
        if(!head) return;

        if(head->id==id){
            Node *t=head;
            head=head->next;
            delete t;
            return;
        }

        Node *cur=head;
        while(cur->next && cur->next->id!=id) cur=cur->next;

        if(cur->next){
            Node *t=cur->next;
            cur->next=t->next;
            delete t;
        }
    }

    void updateStudent(int id){
        Node *temp=head;
        while(temp){
            if(temp->id==id){
                cout<<"Enter New Name: ";
                cin>>temp->name;
                cout<<"Enter New Marks: ";
                cin>>temp->marks;
                return;
            }
            temp=temp->next;
        }
    }

    vector<int> getMarks(){
        vector<int> arr;
        Node *temp=head;
        while(temp){
            arr.push_back(temp->marks);
            temp=temp->next;
        }
        return arr;
    }
};

void merge(vector<int>& arr,int l,int m,int r){
    vector<int> temp;
    int i=l,j=m+1;

    while(i<=m && j<=r){
        if(arr[i]<=arr[j]) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
    }

    while(i<=m) temp.push_back(arr[i++]);
    while(j<=r) temp.push_back(arr[j++]);

    for(int k=l;k<=r;k++) arr[k]=temp[k-l];
}

void mergeSort(vector<int>& arr,int l,int r){
    if(l>=r) return;
    int m=(l+r)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}

int partition(vector<int>& arr,int low,int high){
    int pivot=arr[high];
    int i=low-1;

    for(int j=low;j<high;j++){
        if(arr[j]<pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    }

    swap(arr[i+1],arr[high]);
    return i+1;
}

void quickSort(vector<int>& arr,int low,int high){
    if(low<high){
        int pi=partition(arr,low,high);
        quickSort(arr,low,pi-1);
        quickSort(arr,pi+1,high);
    }
}

int binarySearch(vector<int>& arr,int key){
    int low=0,high=arr.size()-1;

    while(low<=high){
        int mid=(low+high)/2;

        if(arr[mid]==key) return mid;
        if(arr[mid]<key) low=mid+1;
        else high=mid-1;
    }
    return -1;
}

int main(){
    LinkedList list;
    int choice;

    do{
        cout<<"\n===== STUDENT RECORD MANAGEMENT =====\n";
        cout<<"1. Add Student\n2. Delete Student\n3. Update Student\n4. Display Students\n";
        cout<<"5. Merge Sort Marks\n6. Quick Sort Marks\n7. Binary Search Marks\n8. Exit\n";
        cout<<"Enter Choice: ";
        cin>>choice;

        if(choice==1){
            int id,marks;
            string name;
            cout<<"Enter ID: "; cin>>id;
            cout<<"Enter Name: "; cin>>name;
            cout<<"Enter Marks: "; cin>>marks;
            list.addStudent(id,name,marks);
        }
        else if(choice==2){
            int id; cout<<"Enter ID: "; cin>>id;
            list.deleteStudent(id);
        }
        else if(choice==3){
            int id; cout<<"Enter ID: "; cin>>id;
            list.updateStudent(id);
        }
        else if(choice==4){
            list.display();
        }
        else if(choice==5){
            vector<int> arr=list.getMarks();
            if(!arr.empty()){
                mergeSort(arr,0,arr.size()-1);
                cout<<"Sorted Marks: ";
                for(int x:arr) cout<<x<<" ";
            }
        }
        else if(choice==6){
            vector<int> arr=list.getMarks();
            if(!arr.empty()){
                quickSort(arr,0,arr.size()-1);
                cout<<"Sorted Marks: ";
                for(int x:arr) cout<<x<<" ";
            }
        }
        else if(choice==7){
            vector<int> arr=list.getMarks();
            if(!arr.empty()){
                mergeSort(arr,0,arr.size()-1);
                int key;
                cout<<"Enter Marks to Search: ";
                cin>>key;
                int pos=binarySearch(arr,key);
                if(pos!=-1) cout<<"Found at Index "<<pos<<endl;
                else cout<<"Not Found\n";
            }
        }
    }while(choice!=8);

    return 0;
}
