#include "data_structures.h"

int *indexPath_func(int y[]){
  y[1] = robotPath[1].size()-1;
  y[2] = robotPath[2].size()-1;
  return y;
}
std::map<int , point> x1y1_func(){
  std:: map<int  , point> m;
  int j = 0;

  for(int i = 1; i<=10; i++){
    m[i] = {j++*2, 8};

  }
  j=0;

  for (int i = 13; i<=22; i++){
    m[i] = {j++*2, 4};

  }
  j=0;

  for (int i = 30; i<=39; i++){
    m[i] = {j++*2, 0};

  }
  j=0;

  for (int i = 23; i<=25; i++){
    m[i] = {j++*2, 2};

  }

  j=6;

  for (int i = 26; i<=29; i++){
    m[i] = {j++*2, 2};

  }
  m[11] = {0,6};


  m[12] = {18,6};
  return m;

}

std::map<int , point> x2y2_func(){
  std::map<int, point> m;
  int k = 0;
  for(int i = 1; i<=10; i++){

    m[i] = {++k*2, 10};
  }

  k=0;
  for (int i = 13; i<=22; i++){

    m[i] = {++k*2, 6};
  }

  k=0;
  for (int i = 30; i<=39; i++){

    m[i] = {++k*2, 2};
  }

  k=0;
  for (int i = 23; i<=25; i++){

    m[i] = {++k*2, 4};
  }


  k=6;
  for (int i = 26; i<=29; i++){

    m[i] = {++k*2, 4};
  }

  m[11] = {2,8};


  m[11] = {20,8};
  return m;
}

std::map<int , int> NorthGrid_func(){
  std::map<int , int> n_m;
  for(int i = 1; i<=10; i++){
    n_m[i] = -1;
  }
  n_m[11] = 1;
  n_m[12] = 10;
  n_m[13] = 11;
  n_m[22] = 12;
  for(int i = 14; i<=21; i++){
    n_m[i] = -1;
  }
  for(int i = 23; i<=25; i++){
    n_m[i] = i-10;
  }
  for(int i = 26; i<=29; i++){
    n_m[i] = i-7;
  }
  for(int i = 30; i<=32; i++){
    n_m[i] = i-7;
  }
  for(int i = 33; i<=35; i++){
    n_m[i] = -1;
  }
  for(int i = 36; i<=39; i++){
    n_m[i] = i-10;
  }
  return n_m;
}

std::map<int , int>  SouthGrid_func(){
  std::map<int , int> s_m;

  for(int i = 30; i<=39; i++){
    s_m[i] = -1;
  }
  for(int i = 23; i<=25; i++){
    s_m[i] = i+7;
  }
  for(int i = 26; i<=29; i++){
    s_m[i] = i+10;
  }
  for(int i = 13; i<=15; i++){
    s_m[i] = i+10;
  }
  for(int i = 16; i<=18; i++){
    s_m[i] = -1;
  }
  for(int i = 19; i<=22; i++){
    s_m[i] = i+7;
  }
  s_m[11] = 13;
  s_m[12] = 22;
  s_m[1] = 11;
  s_m[10] = 12;
  for(int i = 2; i<=9; i++){
    s_m[i] = -1;
  }
  return s_m;


}

std::map<int , int> EastGrid_func(){
  std::map<int , int> e_m;
  for(int i = 1; i<=9; i++){
    e_m[i] = i+1;
  }
  e_m[10] = -1;
  e_m[11] = -1;
  e_m[12] = -1;
  for(int i = 13; i<=21; i++){
    e_m[i] = i+1;
  }
  e_m[22] = -1;
  for(int i = 23; i<=25; i++){
    e_m[i] = i+1;
  }
  for(int i = 26; i<=28; i++){
    e_m[i] = i+1;
  }
  e_m[29] = -1;
  for(int i = 30; i<=38; i++){
    e_m[i] = i+1;
  }
  e_m[39] = -1;
  return e_m;
}

std::map<int , int> WestGrid_func(){
  std::map<int , int> w_m;

  for(int i = 2; i<=10; i++){
    w_m[i] = i-1;
  }
  w_m[1] = -1;
  w_m[12] = -1;
  w_m[11] = -1;
  w_m[13] = -1;

  for(int i = 14; i<=22; i++){
    w_m[i] = i-1;
  }
  w_m[23] = -1;
  w_m[29] = -1;
  w_m[30] = -1;
  w_m[39] = -1;
  for(int i = 24; i<=25; i++){
    w_m[i] = i-1;
  }
  for(int i = 26; i<=28; i++){
    w_m[i] = i-1;
  }
  for(int i = 31; i<=38; i++){
    w_m[i] = i-1;
  }
  return w_m;
}

std::map<int , std::vector<int> > robotPath_func(){
  std::map<int, std::vector<int>> rp;
  rp[1].push_back(13);
  rp[1].push_back(14);
  rp[1].push_back(15);
  rp[1].push_back(16);
  rp[1].push_back(17);
  rp[1].push_back(18);
  rp[1].push_back(19);
  rp[1].push_back(26);
  rp[1].push_back(36);

  rp[2].push_back(22);
  rp[2].push_back(12);
  rp[2].push_back(10);
  rp[2].push_back(9);
  rp[2].push_back(8);
  rp[2].push_back(7);
  rp[2].push_back(6);
  rp[2].push_back(5);
  return rp;

}

std::map<int , int> robotStatus_func(){
  std::map<int,int> rs;
  rs[1] = -1;
  rs[2] = -1;
  return rs;
}

std::map<int , int> robotCurrentGrid_func(){
  std::map<int,int> rcg;
  rcg[1] = 1;
  rcg[2] = 13;
  return rcg;
}

std::map<int , int> robotNextGrid_func(){
  std::map<int,int> rng;
  rng[1] = 11;
  rng[2] = 29;
  return rng;
}

std::map<int , int> robotDir_func(){
  std::map<int,int> rng;
  rng[1] = 1;
  rng[2] = 0;
  return rng;
}

std::map<int , point> robotPointLocation_func(){
  std::map<int , point> rpl;
  rpl[1] = {1,9};
  rpl[2] = {19,1};
  return rpl;
}

std::map<int , point> obstaclePointLocation_func(){
  std::map<int , point> opl;
  opl[1] = {2,6};
  opl[2] = {6,2};
  return opl;
}

std::map<int, int> obstacleSpan_func(){
  std::map<int, int> osf;
  osf[1] = 8;
  osf[2] = 3;
  return osf;
}



std::map<int , point> x1y1 = x1y1_func();
std::map<int , point> x2y2 = x2y2_func();
std::map<int , int> NorthGrid = NorthGrid_func() ;
std::map<int , int> SouthGrid = SouthGrid_func();
std::map<int , int> EastGrid = EastGrid_func();
std::map<int , int> WestGrid = WestGrid_func();
std::map<int , std::vector<int> > robotPath = robotPath_func();
std::map<int , int> robotStatus= robotStatus_func() ;
std::map<int , int> robotCurrentGrid = robotCurrentGrid_func();
std::map<int , int> robotNextGrid = robotNextGrid_func();
std::map<int , int> robotDir = robotDir_func();
std::map<int , point> robotPointLocation = robotPointLocation_func();
std::map<int , point> obstaclePointLocation = obstaclePointLocation_func();
std::map<int, int> obstacleSpan = obstacleSpan_func();
int iDx[3] = {0,0,0};
int *indexPath = indexPath_func(iDx);
