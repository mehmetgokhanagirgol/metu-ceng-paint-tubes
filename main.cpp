#include <iostream>
#include <vector>

using namespace std;

struct buildings
{
    long l;
    int h;
    int r;
};

vector<buildings> landscape;

void takeInput(){
    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
        landscape.push_back({0,0,0});
        cin >> landscape[i].l >> landscape[i].h >> landscape[i].r;
    }
}

  void appendSkyline(vector<buildings> &output, vector<buildings> skyline, int p, int n, int currh) {
    while (p < n) {
      if (currh != skyline[p].h) {
        if(output.empty() || output.back().l != skyline[p].l){
            output.push_back({skyline[p].l, skyline[p].h, 0});
        }
            else{
                output.back().l = 1;
                output.back().h = skyline[p].h; 
            }
            currh = skyline[p].h;
      }
        p++;
    }
  }


vector<buildings> mergeSkylines(vector<buildings> &left, vector<buildings> &right){
    vector<buildings> output;
    int currh = 0, lefth = 0, righth = 0;
    int pl = 0, pr = 0, nl = left.size(), nr = right.size();
    int x;
    while((pl < nl) && (pr < nr)){
        if(left[pl].l <= right[pr].l){
            x = left[pl].l;
            lefth = left[pl].h;
            pl++;
        }
        else{
            x = right[pr].l;
            righth = right[pr].h;
            pr++;
        }
        if(currh != max(lefth, righth)){
            if(output.empty() || output.back().l != x){
                output.push_back({x, max(lefth, righth), 0});
            }
            else{
                output.back().l = 1;
                output.back().h = max(lefth, righth); 
            }
            currh = max(lefth, righth);
        }
    }

    appendSkyline(output, left, pl, nl, currh);

    appendSkyline(output, right, pr, nr, currh);

    return output;
}

vector<buildings> divideSkyline(vector<buildings> skyline){
    vector<buildings> output;

    if(skyline.size() == 0){
        return output;
    }

    else if(skyline.size() == 1){
        output.push_back({skyline[0].l, skyline[0].h, 0});
        output.push_back({skyline[0].r, 0, 0});
        return output;
    }

    vector<buildings> left;
    vector<buildings> right;

    vector<buildings> sub(&skyline[0], &skyline[(skyline.size())/2]);
    vector<buildings> sub2(&skyline[(skyline.size())/2], &skyline[skyline.size()]);


    left = divideSkyline(sub);
    right = divideSkyline(sub2);

    return mergeSkylines(left, right);
}

int main(){
    unsigned long area = 0;
    takeInput();
    vector<buildings> result = divideSkyline(landscape);
    for(unsigned long i = 0; i < result.size()-1; i++){
        area += abs(result[i+1].l - result[i].l) * result[i].h;
    }
    cout << area << endl;
    return 0;
}