#include <bits/stdc++.h>
using namespace std;

struct Point{
  long long x, y;
};

double PoligonArea(const vector<Point>& fig){
  double res = 0;
  for(unsigned i = 0;i<fig.size();i++){
    Point p = i ? fig[i-1]: fig.back();
    Point q = fig[i];
    res += (p.x - q.x) * (p.y + q.y);
  }
  return fabs(res)/2;
}

double crossProduct(Point A, Point B, Point C){
  return A.x * B.y + B.x * C.y + C.x * A.y - B.y * C.x - C.y * A.x - A.y * B.x;
}

double squaredDistance(Point A, Point B){
  return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

vector<Point> convexHull(vector<Point> &points){
  vector<Point> hull;
  Point lowest = points[0];
  for(unsigned i = 1;i<points.size();i++){
    if(points[i].y < lowest.y || ((points[i].y == lowest.y) && (points[i].x < lowest.x))){
      lowest = points[i];
    }
  }

  sort(points.begin(), points.end(), [&](const Point& A, const Point& B){
    double cp = crossProduct(A,B,lowest);
    if(cp == 0){
      return squaredDistance(A,lowest) < squaredDistance(B, lowest);
    }
    return cp > 0;
  });

  hull.push_back(points[0]);
  hull.push_back(points[1]);
  for(unsigned i = 2;i<points.size();i++){
    while(hull.size() > 1 && crossProduct(hull[hull.size()-2], hull[hull.size()-1], points[i]) < 0){
      hull.pop_back();
    }
    hull.push_back(points[i]);
  }
  return hull;
}
void solve(){
  long long n;
  cin >> n;
  vector<Point> Points;
  vector<Point> sol;
  for(long long i = 0;i<n;i++){
    long long x, y;
    cin >> x >> y;
    Points.emplace_back(Point{x,y});
  }
  //sol = convexHull(Points);
  cout << 2*PoligonArea(Points) << endl;
  /*cout << sol.size() << endl;
  for(Point A : sol){
    cout << A.x << " " << A.y << endl;
  }*/
}
 
 
int main(){
  int t;
  t = 1;
  for(int i = 0;i<t;i++){
    solve();
  }
  return 0;
}  
