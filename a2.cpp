#include <bits/stdc++.h>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

void bubble(vector<int> &v){
    int n=v.size();
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(v[j]>v[j+1]){
                swap(v[j],v[j+1]);
            }
        }
    }
}

void bubblep(vector<int> &v){
    int n=v.size();
   
    for(int i=0;i<n-1;i++){
        #pragma omp parallel for 
        for(int j=0;j<n-i-1;j++){
            if(v[j]>v[j+1]){
                swap(v[j],v[j+1]);
            }
        }
    }
}

void merge(vector<int> &v,int l,int m,int r){
    vector<int> temp;
    int left=l;
    int right=m+1;

    while(left<=m and right<=r){
        if(v[left]<v[right]){
            temp.push_back(v[left]);
            left++;
        }
        else{
            temp.push_back(v[right]);
            right++;
        }
    }

    while(left<=m){
        temp.push_back(v[left]);
        left++;
    }
    while(right<=r){
        temp.push_back(v[right]);
        right++;
    }
    for(int i=l;i<=r;i++){
        v[i]=temp[i-l];
    }
}

void mergesort(vector<int> &v,int l,int r){
    if(l<r){
        int m=(l+r)/2;
        mergesort(v,l,m);
        mergesort(v,m+1,r);

        merge(v,l,m,r);
    }
}

void mergesortp(vector<int> &v,int l,int r){
    if(l<r){
        int m=(l+r)/2;
        #pragma omp parallel sections
        {
            #pragma omp parallel section
            mergesort(v,l,m);
            #pragma omp parallel section
            mergesort(v,m+1,r);

            
        }
        merge(v,l,m,r);
        
    }
}

int main(){
    vector<int> v(10000),u(10000);
    for(int i=0;i<10000;i++){
        v[i]=rand()%1000;
        u[i]=v[i];
    }

    auto start=high_resolution_clock::now();
    bubble(v);
    auto end=high_resolution_clock::now();
    auto time_bubble=duration_cast<milliseconds> (end-start);

    v=u;
    start=high_resolution_clock::now();
    bubblep(v);
    end=high_resolution_clock::now();
    auto time_bubblep=duration_cast<milliseconds> (end-start);

    cout<<time_bubble.count()<<" "<<time_bubblep.count()<<endl;

    v=u;
    start=high_resolution_clock::now();
    mergesort(v,0,9999);
    end=high_resolution_clock::now();
    auto time_merge=duration_cast<milliseconds> (end-start);

    cout<<time_merge.count()<<endl;

    v=u;
    start=high_resolution_clock::now();
    mergesortp(v,0,9999);
    end=high_resolution_clock::now();
    auto time_mergep=duration_cast<milliseconds> (end-start);

    cout<<time_mergep.count()<<endl;


}
