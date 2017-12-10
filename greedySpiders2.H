
////////////NODE ESTATUS//////////////////////
enum Status_spider
{
  SPIDER,
  EMPTY,
  INSECT,
  FISH_HOOK
};

///////////GLOBAL VARIABLES/////////////////
using Nodes = tuple<string, Status_spider,int,int>;
using Node = Graph_Node<Nodes>;
using GT = List_Graph<Node>;
int level_counter = 1;
int aux_num_arcs = 100;

#define WIDTH 900
#define HEIGHT 700
#define BPP 24

//////////////////SDL////////////////////////////////////////////////
SDL_Surface * Init_SDL()
{

  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    cout << "No se ha podido iniciar SDL: "<<  SDL_GetError() << endl;
    exit(1);
  }
  SDL_WM_SetIcon(SDL_LoadBMP("img/icon01.bmp"), NULL);
  return SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);
}

/////////////SPIDER POSICION INTERFAZ//////////////////
void set_spider_pos(GT &graph, SDL_Surface *spider, SDL_Rect &rect_spider)
{
   graph.for_each_node([&](const auto p)
   {
     if(get<1>(p->get_info()) == SPIDER)
     {
       rect_spider.x = get_node_xcoordinate(p)-spider->w/3;
       rect_spider.y = get_node_ycoordinate(p)-spider->h/3;
       rect_spider.w = spider->w;
       rect_spider.h = spider->h;
       }
     });
}

/////////////INSECT POSICION INTERFAZ//////////////////
void set_insect_pos(GT &graph, SDL_Surface *insect[], SDL_Rect rect_insect[])
{
  int i = 0;

   graph.for_each_node([&](const auto p)
   {

     if(get<1>(p->get_info()) == INSECT)
     {
     
      insect[i] = IMG_Load("img/png/red/butterfly.png");
      if(insect[i] == NULL)
      {
        cout << "ERROR: " << SDL_GetError() << endl;
        return;
      }
       rect_insect[i].x = get_node_xcoordinate(p)-insect[i]->w/2;
       rect_insect[i].y = get_node_ycoordinate(p)-insect[i]->h/2;
       rect_insect[i].w = insect[i]->w;
       rect_insect[i].h = insect[i]->h;
       i++;
     } 
   });
}

/////////////FISH HOOK POSICION INTERFAZ//////////////////
void set_fish_hook_pos(GT &graph, SDL_Surface *fish_hook, SDL_Rect &rect_fish_hook)
{
   graph.for_each_node([&](const auto p)
   {
     if(get<1>(p->get_info()) == FISH_HOOK)
     {
       rect_fish_hook.x = get_node_xcoordinate(p)-fish_hook->w/2;
       rect_fish_hook.y = get_node_ycoordinate(p)-fish_hook->h/2;
       rect_fish_hook.w = fish_hook->w;
       rect_fish_hook.h = fish_hook->h;
     }
   });
}

/////////////////////////////////////////////////////////
int get_node_xcoordinate(GT::Node * p)
{
  return get<2>(p->get_info());
}

/////////////////////////////////////////////////////////
int get_node_ycoordinate(GT::Node * p)
{
  return get<3>(p->get_info());
}

///////////////////////////////////////////////////////
SDL_Surface * load_IMG_spider()
{
  SDL_Surface *spider;
  spider = IMG_Load("img/png/red/spider.png");
  if(spider == NULL)
  {
   cout << "No se ha podido cargar la imagen: " << SDL_GetError() << endl;
   exit(1);
  }
  return spider;
}

////////////////////////////////////////////////////////
SDL_Surface * load_IMG_fire(bool color)
{
  SDL_Surface *fire;

  if(color)
   fire = IMG_Load("img/png/red/fire1.png");
  else
    fire = IMG_Load("img/png/red/fire.png");
  
  if(fire == NULL)
  {
    cout << "No se ha podido cargar la imagen: " << SDL_GetError() << endl;
    exit(1);
  };
  return fire;
}

//////////////////////////////////////////////////////////
SDL_Surface * load_IMG_ant(bool color)
{
  SDL_Surface *ant;
  if(color)
    ant = IMG_Load("img/png/red/ant1.png");
  else
    ant = IMG_Load("img/png/red/ant.png");

  if(ant == NULL)
  {
    cout << "No se ha podido cargar la imagen: " << SDL_GetError() << endl;
    exit(1);
  }
  return ant;
}

////////////////////////////////////////////////////////////
SDL_Surface * load_IMG_ice(bool color)
{
  SDL_Surface *ice;
  if(color)
    ice = IMG_Load("img/png/red/ice1.png");
  else
    ice = IMG_Load("img/png/red/ice.png");

  if(ice == NULL)
  {
    cout << "No se ha podido cargar la imagen: " << SDL_GetError() << endl;
    exit(1);
  }
  return ice;
}

//////////////////////////////////////////////////////////////
SDL_Surface * load_IMG_right(bool color)
{
  SDL_Surface *right;
  if(color)
    right = IMG_Load("img/png/red/right1.png");
  else
    right = IMG_Load("img/png/red/right.png");

  if(right == NULL)
  {
    cout << "No se ha podido cargar la imagen: " << SDL_GetError() << endl;
    exit(1);
  }
  return right;
}

///////////////////////////////////////////////////////////////
SDL_Surface * load_IMG_glue(bool color)
{ 
  SDL_Surface *glue;
  if(color)
    glue = IMG_Load("img/png/red/glue1.png");
  else
    glue = IMG_Load("img/png/red/glue.png");

  if(glue == NULL)
  {
    cout << "No se ha podido cargar la imagen: " << SDL_GetError() << endl;
    exit(1);
  }
  return glue;

}

//////////////////////////////////////////////////////////////
SDL_Surface * load_IMG_insect()
{
  SDL_Surface *insect;

  insect = IMG_Load("img/png/red/butterfly.png");
  
  if(insect == NULL)
  {
    cout << "No se ha podido cargar la imagen: " << SDL_GetError() << endl;
    exit(1);
  }
  return insect;
}

SDL_Surface * load_IMG_fish_hook()
{
  SDL_Surface *fish_hook;

  fish_hook= IMG_Load("img/png/red/ant2.png");
  
  if(fish_hook == NULL)
  {
    cout << "No se ha podido cargar la imagen: " << SDL_GetError() << endl;
    exit(1);
  }
  return fish_hook;
}

///////////////////////////////////////////////////////////////
void BlitSurface_bandw_icon(SDL_Surface *screen, SDL_Rect &rect_fire0,SDL_Rect &rect_glue0, SDL_Rect &rect_ant0,
                            SDL_Rect &rect_ice0,SDL_Rect &rect_right0, SDL_Surface *fire_bandw, SDL_Surface *glue_bandw,
                            SDL_Surface *ant_bandw,SDL_Surface *ice_bandw,SDL_Surface *right_bandw)
{
            SDL_BlitSurface(fire_bandw, NULL, screen, &rect_fire0);
            SDL_BlitSurface(glue_bandw, NULL, screen, &rect_glue0);
            SDL_BlitSurface(ant_bandw, NULL, screen, &rect_ant0);
            SDL_BlitSurface(ice_bandw, NULL, screen, &rect_ice0);
            SDL_BlitSurface(right_bandw, NULL, screen, &rect_right0);
}

///////////////////CALCULATE ANGLE//////////////////////////////////
float calculate_angle(Node * node_src, Node * node_tgt)
{
  float CO = get<3>(node_tgt->get_info()) - get<3>(node_src->get_info()); 
  float CA = get<2>(node_tgt->get_info()) - get<2>(node_src->get_info()); 
  float m = CO/CA;
  float angle = atan(m)*57.296*-1;

  return angle;
}

/////////////////LOAD IMAGES/////////////////////////////////////
void painting_nodes_on_screen(GT &graph, SDL_Rect rect_circle[], SDL_Surface *circle[])
{
  int i =0;

  graph.for_each_node([&](const auto p)
  {
    circle[i] = IMG_Load("img/png/red/nodo.png");
    if(circle[i] == NULL)
    {
      cout << "No se ha podido cargar la imagen: " << SDL_GetError() << endl;
      return;
    }
    rect_circle[i].x = get_node_xcoordinate(p);
    rect_circle[i].y = get_node_ycoordinate(p);
    i++;
  }); 
}

void painting_arcs_on_screen(GT &graph, SDL_Rect rect_arc[], SDL_Surface *arc3[])
{
  SDL_Surface *circle, *arc, *arc2;
  arc = IMG_Load("img/png/red/hilo01.png");
  circle = IMG_Load("img/png/red/nodo.png");
  string label;

  if(arc == NULL)
  {
    cout << "No se ha podido cargar la imagen: " << SDL_GetError() << endl;
    return;
  }

  int i_arc =0;

  graph.for_each_arc([&](const auto p)
  {
    Node * node_src = graph.get_src_node(p);
    Node * node_tgt = graph.get_tgt_node(p);

    label = get<0>(node_src->get_info()) + get<0>(node_tgt->get_info());

    float angle = calculate_angle(node_src, node_tgt);

    arc2 = rotozoomSurface(arc, angle,1 ,0 );

    if(label == "AB" or label == "CD" or label == "ED" or label == "AF")
    {
      arc3[i_arc] = zoomSurface(arc2,0.53,0.53, SMOOTHING_ON);

      if(label == "AB" or label == "ED")
      {
        rect_arc[i_arc].x = get_node_xcoordinate(node_src)+2;
        rect_arc[i_arc].y = get_node_ycoordinate(node_src)- arc3[i_arc]->h + (circle->h)/2;
      }

      if(label == "CD" or label == "AF")
      {
        rect_arc[i_arc].x = get_node_xcoordinate(node_src);
        rect_arc[i_arc].y = get_node_ycoordinate(node_src)+ (circle->h)/2;
      }
    }

    if(label == "AG" or label == "GD")
    {
      arc3[i_arc] = zoomSurface(arc2,0.75,0.75, SMOOTHING_ON);

        rect_arc[i_arc].x = get_node_xcoordinate(node_src)+ (circle->w)/2;
        rect_arc[i_arc].y = get_node_ycoordinate(node_src)- (circle->h)/3 ;
      
    }

    if(label == "BC" or label == "FE")
    {
      arc3[i_arc] = arc;

        rect_arc[i_arc].x = get_node_xcoordinate(node_src)+ (circle->w)/2;
        rect_arc[i_arc].y = get_node_ycoordinate(node_src)- (circle->h)/2;
    }

    if(label == "BG" or label == "CG" or label == "EG" or label == "FG")
    {
      arc3[i_arc] = zoomSurface(arc2,0.7,0.7, SMOOTHING_ON);

      if(label == "BG")
      {
        rect_arc[i_arc].x = get_node_xcoordinate(node_src);
        rect_arc[i_arc].y = get_node_ycoordinate(node_src);
      }

      if(label == "CG")
      {
        rect_arc[i_arc].x = get_node_xcoordinate(node_src) - arc3[i_arc]->h + (circle->h);
        rect_arc[i_arc].y = get_node_ycoordinate(node_src);
      }

      if(label == "EG")
      {
        rect_arc[i_arc].x = get_node_xcoordinate(node_src)+ (circle->h) - arc3[i_arc]->w;
        rect_arc[i_arc].y = get_node_ycoordinate(node_src)+ (circle->h) - arc3[i_arc]->h;
      }

      if(label == "FG")
      {
        rect_arc[i_arc].x = get_node_xcoordinate(node_src);
        rect_arc[i_arc].y = get_node_ycoordinate(node_src) - arc3[i_arc]->h + (circle->h);
      }
    }

    i_arc++;
  }); 
}

void painting_arcs_on_screen2(GT &graph, SDL_Rect rect_arc[], SDL_Surface *arc3[])
{
  SDL_Surface *circle, *arc, *arc2;
  arc = IMG_Load("img/png/red/hilo01.png");
  circle = IMG_Load("img/png/red/nodo.png");
  string label;
  float angle;


  if(arc == NULL)
  {
    cout << "No se ha podido cargar la imagen: " << SDL_GetError() << endl;
    return;
  }

  int i_arc =0;
 
  graph.for_each_arc([&](const auto p)
  {
    Node * node_src = graph.get_src_node(p);
    Node * node_tgt = graph.get_tgt_node(p);

    label = get<0>(node_src->get_info()) + get<0>(node_tgt->get_info());

   // cout << label <<":";

    if(label == "BC" or label == "LI" or label == "ID" or label == "AL" or 
        label == "HK" or label == "KJ" or label == "JE" or label == "GF")
    {
      angle = calculate_angle(node_src, node_tgt);
      arc2 = rotozoomSurface(arc, angle,1 ,0 );
      arc3[i_arc] = zoomSurface(arc2,0.41,0.41, SMOOTHING_ON);

        rect_arc[i_arc].x = get_node_xcoordinate(node_src) + 7;
        rect_arc[i_arc].y = get_node_ycoordinate(node_src)- arc3[i_arc]->h + circle->h - 3;
    }
    if(label == "CD" or label == "BI" or label == "IE" or label == "LJ" or 
        label == "AK" or label == "KF" or label == "HG")
    {
      angle = calculate_angle(node_src, node_tgt);
      arc2 = rotozoomSurface(arc, angle,1 ,0 );
      arc3[i_arc] = zoomSurface(arc2,0.47,0.47, SMOOTHING_ON);

        rect_arc[i_arc].x = get_node_xcoordinate(node_src) + circle->h/2 + 4;
        rect_arc[i_arc].y = get_node_ycoordinate(node_src);
    }

    if (label == "CI" or label == "IJ" or label == "JF" or label == "DE" or label == "KG" or
        label == "LK" or label == "BL" or label == "AH")
    {
      angle = calculate_angle(node_src, node_tgt);
      arc2 = rotozoomSurface(arc, angle,1 ,0 );
      arc3[i_arc] = zoomSurface(arc2,0.39,0.39, SMOOTHING_ON);

        rect_arc[i_arc].x = get_node_xcoordinate(node_src) + circle->h/2 - 4;
        rect_arc[i_arc].y = get_node_ycoordinate(node_src) + circle->h/2 - 4;
    }
    if (label == "BA" or label == "FE")
    {
      angle = calculate_angle(node_src, node_tgt);
      arc2 = rotozoomSurface(arc, angle,1 ,0 );
      arc3[i_arc] = zoomSurface(arc2,0.65,0.65, SMOOTHING_ON);

      if (label == "BA")
      {
        rect_arc[i_arc].x = get_node_xcoordinate(node_src) - 5;
        rect_arc[i_arc].y = get_node_ycoordinate(node_src) + circle->h/2;
      }

      if (label == "FE")
      {
        rect_arc[i_arc].x = get_node_xcoordinate(node_src);
        rect_arc[i_arc].y = get_node_ycoordinate(node_src) + circle->h/2 - arc3[i_arc]->h;
      }
        
    }

    i_arc++;
  }); 
}

void painting_arcs_on_screen3(GT &graph, SDL_Rect rect_arc[], SDL_Surface *arc3[])
{
  SDL_Surface *circle, *arc, *arc2;
  arc = IMG_Load("img/png/red/hilo01.png");
  circle = IMG_Load("img/png/red/nodo.png");
  string label;
  float angle;


  if(arc == NULL)
  {
    cout << "No se ha podido cargar la imagen: " << SDL_GetError() << endl;
    return;
  }

  int i_arc =0;
 
  graph.for_each_arc([&](const auto p)
  {
    Node * node_src = graph.get_src_node(p);
    Node * node_tgt = graph.get_tgt_node(p);

    label = get<0>(node_src->get_info()) + get<0>(node_tgt->get_info());

    //cout << label <<":";

    if(label == "AB" or label == "CE" or label == "GH" or label == "IK" or 
        label == "DC" or label == "FG" or label == "JI" or label == "ML")
    {
      angle = calculate_angle(node_src, node_tgt);
      arc2 = rotozoomSurface(arc, angle,1 ,0 );
      arc3[i_arc] = zoomSurface(arc2,0.57,0.57, SMOOTHING_ON);

        rect_arc[i_arc].x = get_node_xcoordinate(node_src);
        rect_arc[i_arc].y = get_node_ycoordinate(node_src)- arc3[i_arc]->h + circle->h/2 + 7;
    }
    if(label == "AD" or label == "CF" or label == "GJ" or label == "IM" or 
        label == "BC" or label == "EG" or label == "HI" or label == "KL")
    {
      angle = calculate_angle(node_src, node_tgt);
      arc2 = rotozoomSurface(arc, angle,1 ,0 );
      arc3[i_arc] = zoomSurface(arc2,0.57,0.57, SMOOTHING_ON);

        rect_arc[i_arc].x = get_node_xcoordinate(node_src);
        rect_arc[i_arc].y = get_node_ycoordinate(node_src) + circle->h/2 - 6;
    }
    if (label == "BE" or label == "EH" or label == "HK" or label == "DF" or label == "FJ" or
        label == "JM" or label == "AC" or label == "CG" or label == "GI" or label == "IL")
    {
      angle = calculate_angle(node_src, node_tgt);
      arc2 = rotozoomSurface(arc, angle,1 ,0 );
      arc3[i_arc] = zoomSurface(arc2,0.57,0.57, SMOOTHING_ON);

        rect_arc[i_arc].x = get_node_xcoordinate(node_src) + circle->h/2 + 4;
        rect_arc[i_arc].y = get_node_ycoordinate(node_src);
    }

    i_arc++;
  }); 
}

//////////////////////////REFRESH///////////////////////////////
void refresh_arcs(SDL_Surface *screen, SDL_Rect rect_arc[], SDL_Surface *arc3[], int num_arcs)
{
  for (int ii = 0; ii < num_arcs; ++ii)
  {
    SDL_BlitSurface(arc3[ii], NULL, screen, &rect_arc[ii]);
  }
}

void refresh_node(SDL_Surface *screen, SDL_Rect rect_circle[], SDL_Surface *circle[], int n)
{
  for (int ii = 0; ii < n; ++ii)
  {
    SDL_BlitSurface(circle[ii], NULL, screen, &rect_circle[ii]);
    
  }
}

void refresh_insect(SDL_Surface *screen, SDL_Rect rect_insect[], SDL_Surface *insect[], int num_insect)
{
  for (int ii = 0; ii < num_insect; ii++)
  {
    SDL_BlitSurface(insect[ii], NULL, screen, &rect_insect[ii]);  
  }
}

//////////////MOVE TO SPIDER SCREEN/////////////////////////////
void moving_spider_on_screen(Node *nodo_aux, Node *nodo_aux2, SDL_Rect rect_insect[], SDL_Rect rect_spider, SDL_Surface *spider, SDL_Surface *insect[],
                           SDL_Surface *background, SDL_Surface *screen, SDL_Rect &rect_fire0,SDL_Rect &rect_glue0, SDL_Rect &rect_ant0,
                           SDL_Rect &rect_ice0,SDL_Rect &rect_right0, SDL_Surface *fire_bandw, SDL_Surface *glue_bandw, SDL_Surface *ant_bandw,
                           SDL_Surface *ice_bandw,SDL_Surface *right_bandw, SDL_Rect rect_arc[], SDL_Surface *arc3[], int num_arcs, 
                           SDL_Rect rect_circle[], SDL_Surface *circle[], int n, int num_insect)
{
  int x2 = get_node_xcoordinate(nodo_aux2);
  int y2 = get_node_ycoordinate(nodo_aux2);
  int x1 = get_node_xcoordinate(nodo_aux);
  int y1 = get_node_ycoordinate(nodo_aux);
  float x = x1, y = y1;

  float num = (y2-y1);
  float den = (x2-x1);
  float m = num/den;

  ///////////CASE 1////////////////
   while(x <= x2 and den != 0)
   { 
     x = x + 5;
     y = x*m + y1 - m*x1; 

     rect_spider.x = x-spider->w/3;
     rect_spider.y = y-spider->h/3;

     SDL_BlitSurface(background, NULL, screen, NULL);
     BlitSurface_bandw_icon(screen, rect_fire0, rect_glue0, rect_ant0, rect_ice0, rect_right0,fire_bandw,
                    glue_bandw,ant_bandw,ice_bandw,right_bandw);
   	 refresh_arcs(screen, rect_arc, arc3, num_arcs);
     refresh_node(screen,rect_circle, circle, n);
	 refresh_insect(screen,rect_insect,insect,num_insect);
     SDL_BlitSurface(spider, NULL, screen, &rect_spider);
     SDL_Flip(screen);
   }

   /////////////CASE 2//////////////////
   while(x >= x2 and den != 0)
   { 
     x = x - 5;
     y = x*m + y1 - m*x1;

     rect_spider.x = x-spider->w/3;
     rect_spider.y = y-spider->h/3;

     SDL_BlitSurface(background, NULL, screen, NULL);       
     BlitSurface_bandw_icon(screen, rect_fire0, rect_glue0, rect_ant0, rect_ice0, rect_right0,fire_bandw,
                            glue_bandw,ant_bandw,ice_bandw,right_bandw);
     refresh_arcs(screen, rect_arc, arc3, num_arcs);
     refresh_node(screen,rect_circle, circle, n);
     refresh_insect(screen,rect_insect,insect,num_insect);
     SDL_BlitSurface(spider, NULL, screen, &rect_spider);
     SDL_Flip(screen);
   }

   /////////CASE 3/////////////////
   while(x == x2 and y > y2)
   { 
     y = y - 5;   

     rect_spider.x = x-spider->w/3;
     rect_spider.y = y-spider->h/3;

     SDL_BlitSurface(background, NULL, screen, NULL);
     BlitSurface_bandw_icon(screen, rect_fire0, rect_glue0, rect_ant0, rect_ice0, rect_right0,fire_bandw,
                                   glue_bandw,ant_bandw,ice_bandw,right_bandw);
     refresh_arcs(screen, rect_arc, arc3, num_arcs);
     refresh_node(screen,rect_circle, circle, n);
     refresh_insect(screen,rect_insect,insect,num_insect);
     SDL_BlitSurface(spider, NULL, screen, &rect_spider);
     SDL_Flip(screen);
   }

  /////////CASE 4/////////////
  while(x == x2 and y < y2)
  { 
    y = y + 5;   

    rect_spider.x = x-spider->w/3;
    rect_spider.y = y-spider->h/3;

    SDL_BlitSurface(background, NULL, screen, NULL);
    BlitSurface_bandw_icon(screen, rect_fire0, rect_glue0, rect_ant0, rect_ice0, rect_right0,fire_bandw,
                                   glue_bandw,ant_bandw,ice_bandw,right_bandw);
    refresh_arcs(screen, rect_arc, arc3, num_arcs);
    refresh_node(screen,rect_circle, circle, n);
     refresh_insect(screen,rect_insect,insect,num_insect);
    SDL_BlitSurface(spider, NULL, screen, &rect_spider);
    SDL_Flip(screen);
  }

}

///////////BUILD_GRAPH///////////////////////////////////////////////
void Build_Graph(GT &graph)
{
  int w = WIDTH;
  int h = HEIGHT-100;
  auto A = graph.insert_node(make_tuple("A",SPIDER,w/4,h/2));
  auto B = graph.insert_node(make_tuple("B",EMPTY,w/3,h/4));
  auto C = graph.insert_node(make_tuple("C",EMPTY,w/3+w/3,h/4));
  auto D = graph.insert_node(make_tuple("D",INSECT,w/4+w/2,h/2));
  auto E = graph.insert_node(make_tuple("E",EMPTY,w/3+w/3,h/4+h/2));
  auto F = graph.insert_node(make_tuple("F",EMPTY,w/3,h/4+h/2));
  auto G = graph.insert_node(make_tuple("G",EMPTY,w/2,h/2));
  
  graph.insert_arc(A, B);
  graph.insert_arc(A, G);
  graph.insert_arc(B, C);
  graph.insert_arc(B, G);
  graph.insert_arc(C, D);
  graph.insert_arc(C, G);
  graph.insert_arc(E, D);
  graph.insert_arc(G, D);
  graph.insert_arc(F, E);
  graph.insert_arc(E, G);
  graph.insert_arc(A, F);
  graph.insert_arc(F, G);

}

void Build_Graph2(GT &graph)
{
  int w = WIDTH;
  int h = HEIGHT-100;

  auto A = graph.insert_node(make_tuple("A",EMPTY,w/3,5*h/6-100));
  auto B = graph.insert_node(make_tuple("B",SPIDER,w/3,h/2-100));
  auto C = graph.insert_node(make_tuple("C",EMPTY,5*w/12,h/3-100));
  auto D = graph.insert_node(make_tuple("D",EMPTY,7*w/12,h/3-100));
  auto E = graph.insert_node(make_tuple("E",EMPTY,2*w/3,h/2-100));
  auto F = graph.insert_node(make_tuple("F",EMPTY,2*w/3,5*h/6-100));
  auto G = graph.insert_node(make_tuple("G",INSECT,7*w/12,h-100));
  auto H = graph.insert_node(make_tuple("H",EMPTY,5*w/12,h-100));
  auto I = graph.insert_node(make_tuple("I",EMPTY,w/2,h/2-100));
  auto J = graph.insert_node(make_tuple("J",EMPTY,7*w/12,2*h/3-100));
  auto K = graph.insert_node(make_tuple("K",EMPTY,w/2,5*h/6-100));
  auto L = graph.insert_node(make_tuple("L",EMPTY,5*w/12,2*h/3-100));
  
  graph.insert_arc(B, C);
  graph.insert_arc(L, I);
  graph.insert_arc(I, D);
  graph.insert_arc(J, E);
  graph.insert_arc(A, L);
  graph.insert_arc(H, K);
  graph.insert_arc(K, J);
  graph.insert_arc(G, F);

  graph.insert_arc(C, D);
  graph.insert_arc(B, I);
  graph.insert_arc(I, E);
  graph.insert_arc(L, J);
  graph.insert_arc(A, K);
  graph.insert_arc(K, F);
  graph.insert_arc(H, G);

  graph.insert_arc(C, I);
  graph.insert_arc(I, J);
  graph.insert_arc(J, F);
  graph.insert_arc(D, E);
  graph.insert_arc(K, G);
  graph.insert_arc(L, K);
  graph.insert_arc(B, L);
  graph.insert_arc(A, H);

  graph.insert_arc(B, A);
  graph.insert_arc(F, E);

}

void Build_Graph3(GT &graph)
{
  int w = WIDTH;
  int h = HEIGHT-100;

  auto A = graph.insert_node(make_tuple("A",SPIDER,w/10,h/2));
  auto B = graph.insert_node(make_tuple("B",EMPTY,w/5,h/4));
  auto C = graph.insert_node(make_tuple("C",EMPTY,3*w/10,h/2));
  auto D = graph.insert_node(make_tuple("D",EMPTY,w/5,3*h/4));
  auto E = graph.insert_node(make_tuple("E",EMPTY,2*w/5,h/4));
  auto F = graph.insert_node(make_tuple("F",EMPTY,2*w/5,3*h/4));
  auto G = graph.insert_node(make_tuple("G",INSECT,w/2,h/2));
  auto H = graph.insert_node(make_tuple("H",EMPTY,3*w/5,h/4));
  auto I = graph.insert_node(make_tuple("I",EMPTY,7*w/10,h/2));
  auto J = graph.insert_node(make_tuple("J",EMPTY,3*w/5,3*h/4));
  auto K = graph.insert_node(make_tuple("K",EMPTY,4*w/5,h/4));
  auto L = graph.insert_node(make_tuple("L",EMPTY,9*w/10,h/2));
  auto M = graph.insert_node(make_tuple("M",EMPTY,4*w/5,3*h/4));
  
  graph.insert_arc(A, B);
  graph.insert_arc(C, E);
  graph.insert_arc(G, H);
  graph.insert_arc(I, K);
  graph.insert_arc(D, C);
  graph.insert_arc(F, G);
  graph.insert_arc(J, I);
  graph.insert_arc(M, L);

  graph.insert_arc(A, D);
  graph.insert_arc(C, F);
  graph.insert_arc(G, J);
  graph.insert_arc(I, M);
  graph.insert_arc(B, C);
  graph.insert_arc(E, G);
  graph.insert_arc(H, I);
  graph.insert_arc(K, L);

  graph.insert_arc(B, E);
  graph.insert_arc(E, H);
  graph.insert_arc(H, K);
  graph.insert_arc(D, F);
  graph.insert_arc(F, J);
  graph.insert_arc(J, M);
  graph.insert_arc(A, C);
  graph.insert_arc(C, G);
  graph.insert_arc(G, I);
  graph.insert_arc(I, L);
}

///////////SELECT LEVEL//////////////////////////////////////
DynArray<size_t> powers;
bool exist_path = true;
size_t i1 = 0, i2 = 1, i3 = 1, i4 = 0, i5 = 0;

void Select_level(GT &graph ,int level)
{
  clear_graph(graph);
  aux_num_arcs = 100;

    switch (level)
    {
      case 1:
      {  
        Build_Graph(graph);
        powers = {i1,i2,i3,i4,i5};
        break;
      }  

      case 2: 
      {  
        Build_Graph2(graph);
        i1++, i2++, i3++, i4++;
        powers = {i1,i2,i3,i4,0};
        exist_path = true;
        break;

      }

      case 3:  
      { 
        Build_Graph3(graph);
        i1++, i2++, i3++, i5++;
        powers = {i1,i2,i3,i4,i5};
        exist_path = true;
        break;
      }

      default: 
      {
        Build_Graph(graph);
        powers = {0,1,1,0,0};
        break;
      }
        return;
    }
} 

//////////////////POSICION INSECT///////////////////////////////
string posicion_insect(GT &graph)
{
  string aux_fish_insect;


    graph.for_each_node([&](const auto aux)
    {
      if (get<1>(aux->get_info()) == INSECT)
        aux_fish_insect = get<0>(aux->get_info());;
    });

return aux_fish_insect;
}

string posicion_insect_2(GT &graph, string first_insect)
{
  string aux_fish_insect;
  

    graph.for_each_node([&](const auto aux)
    {
      if (get<1>(aux->get_info()) == INSECT and get<0>(aux->get_info()) != first_insect)
        aux_fish_insect = get<0>(aux->get_info());
    });

return aux_fish_insect;
}

//////////////////POSICION SPIDER//////////////////////////////
string posicion_spider(GT &graph)
{
  string aux_spider;

    graph.for_each_node([&](const auto aux)
    {
      if (get<1>(aux->get_info()) == SPIDER)
        aux_spider = get<0>(aux->get_info());
    });

return aux_spider;
}

//////////////////POSICION FISH HOOK//////////////////////////////
string posicion_fish_hook(GT &graph)
{
  string aux_fish_hook;

    graph.for_each_node([&](const auto aux)
    {
      if (get<1>(aux->get_info()) == FISH_HOOK)
        aux_fish_hook = get<0>(aux->get_info());
    });

return aux_fish_hook;
}

///////////////FIND PATH/////////////////////////////////////////
Path<GT > Finding_Path(GT &graph, string aux_start, string aux_end)
{
  Node * start, * end;
 
    graph.for_each_node([&](const auto aux)
    {
      if (get<0>(aux->get_info()) == aux_start)
        start = aux;

      if (get<0>(aux->get_info()) == aux_end)
        end = aux;
    });

    auto path = find_path_breadth_first(graph, start, end);

  return path;
}

int get_num_insect_on_level(GT &graph)
{
    int num_insect = 0;
    graph.for_each_node([&](const auto p)
    {
      if ( get<1>(p->get_info()) == INSECT)
        num_insect++;  
    }); 
  return num_insect;
}

///////////////////IS_GAME_OVER?////////////////////////////////
bool continue_game = true;
void is_game_over(GT &graph, string aux_fish_insect, string aux_fish_insect_2)
{

    graph.for_each_node([&](const auto variable)
    {
       if (get<0>(variable->get_info()) == aux_fish_insect)
       {
          if (get<1>(variable->get_info()) == SPIDER)
          {
            continue_game = false;
            cout << "   ---GAME OVER---  " << endl<< endl;   
          }
       }

       if (get<0>(variable->get_info()) == aux_fish_insect_2)
       {
          if (get<1>(variable->get_info()) == SPIDER)
          {
            continue_game = false;
            cout << "   ---GAME OVER---  " << endl<< endl;   
          }
       }

    });

  return;
}

//////////////////PLAY//////////////////////////////////////////
bool init = true;
bool init2 = true;

void play(GT &graph)
{
  	///////////////VARIABLES SDL/////////////////////////////////////////
  	SDL_Surface *screen, *background,*fire_bandw, *ice_bandw, *ant_bandw, *right_bandw, *glue_bandw,*fish_hook;
  	SDL_Surface *spider;
  	SDL_Rect rect_fire0, rect_right0,rect_glue0,rect_ice0,rect_ant0;
  	SDL_Rect rect_spider, rect_fish_hook;
  	SDL_Surface *init_wallpaper, *wallpaper0;
  	SDL_Event event;
  	int mousex, mousey, aux_mousex, aux_mousey;

  	screen = Init_SDL();

  	/////////////GAME WINDOW CAPTION///////////////
  	SDL_WM_SetCaption("G R E E D Y     S P I D E R S",NULL);
  	background = SDL_LoadBMP("img/wallpaper.bmp");

 	///////////VARIABLES C++///////////////////////////////////////////////
  	string aux_spider, aux_fish_insect, aux_fish_hook, aux_hook, aux_fish_insect_2;
  	Node * nodo_aux , * nodo_aux2, * nodo_aux_hook, *nodo_aux2_hook, *nodo_aux_insect_2, *nodo_aux2_insect_2;
  	size_t exist_power = 0;
  	bool fire_power = true, ant_power = true, right_power = true ;

 	//loading images; 1 -> load b&w icons (just for powers icons)
 	spider = load_IMG_spider();
  	fire_bandw = load_IMG_fire(1);
 	ant_bandw = load_IMG_ant(1);
 	ice_bandw = load_IMG_ice(1);
 	right_bandw = load_IMG_right(1);
	glue_bandw = load_IMG_glue(1);
  	fish_hook = load_IMG_fish_hook();

  	//fire power position
  	rect_fire0.x = 800;
  	rect_fire0.y = 620;

  	//ant power position
  	rect_ant0.x = 720;
  	rect_ant0.y = 620;

  	//ice power position
  	rect_ice0.x = 640;
  	rect_ice0.y = 620;

  	//glue power position
  	rect_glue0.x = 560;
  	rect_glue0.y = 620;

  	//move power position
  	rect_right0.x = 480;
  	rect_right0.y = 620;

  	int n = graph.get_num_nodes();
  	int num_arcs = graph.get_num_arcs();
  	int num_insect = get_num_insect_on_level(graph);

  	SDL_Rect rect_circle[n];
  	SDL_Surface *circle[n];

  	SDL_Rect rect_arc[num_arcs];
  	SDL_Surface *arc3[num_arcs];

  	SDL_Rect rect_insect[num_insect];
 	SDL_Surface *insect[num_insect];

  	while(init == true)
  	{  	
      	init2 = true;
      	init_wallpaper = IMG_Load("img/fondo.bmp");

      	SDL_Rect play_rect, button_rect;
      	SDL_Surface * play, *button;

      	play = IMG_Load("img/png/play.png");
      	play_rect.x = WIDTH/2 + WIDTH/4;
      	play_rect.y = HEIGHT/2 + HEIGHT/3;

      	button = IMG_Load("img/png/3.png");
      	button_rect.x = WIDTH/2 + WIDTH/3 + 50;
      	button_rect.y = HEIGHT/2 + HEIGHT/3;

      	SDL_BlitSurface(init_wallpaper, NULL, screen, NULL);
      	SDL_BlitSurface(play, NULL, screen, &play_rect);
      	SDL_BlitSurface(button, NULL, screen, &button_rect);
      	SDL_Flip(screen);

      	while (SDL_PollEvent(&event))
      	{

      		if(event.type == SDL_QUIT)
      		{
      			init = false;
        		SDL_Quit();
        		exit (0);
      		}

      		SDL_GetMouseState(&mousex, &mousey);

      		if (event.type == SDL_MOUSEBUTTONDOWN)
      		{
      			SDL_GetMouseState(&mousex, &mousey);

      			if (event.button.button ==  SDL_BUTTON_LEFT)
      			{
      				if (mousex >= play_rect.x and mousex <= play_rect.x + play_rect.w 
      				and mousey >= play_rect.y and play_rect.y + play_rect.h)
      				{
      					init = false;
      				}

      				if (mousex >= button_rect.x and mousex <= button_rect.x + button_rect.w 
      				and mousey >= button_rect.y and button_rect.y + button_rect.h)
      				{
      		    		while (init2 == true)
                   		{
               	    		if(event.type == SDL_QUIT)
                       		{
                           		init = false;
                           		SDL_Quit();
                           		exit (0);
                       		}

      			    		wallpaper0 = IMG_Load("img/wallpaper0.bmp");

                       		SDL_BlitSurface(wallpaper0, NULL, screen, NULL);
                       		SDL_BlitSurface(play, NULL, screen, &play_rect);
      			    		SDL_Flip(screen);
 
                       		while (SDL_PollEvent(&event))
                       		{
      	                   		SDL_GetMouseState(&mousex, &mousey);

      	           				if (event.type == SDL_MOUSEBUTTONDOWN)
      	           				{
      		           				SDL_GetMouseState(&mousex, &mousey);

                       				if (event.button.button ==  SDL_BUTTON_LEFT)
      		           				{
      		          					if (mousex >= play_rect.x and mousex <= play_rect.x + play_rect.w 
      			        				and mousey >= play_rect.y and play_rect.y + play_rect.h)
      		          					{
      		          						init2 = false;
      		          						init = false;
      		          					}
                       				}
                   				}
                   			}
      		   			}
      				}
      			}      		
      		}
      	}
    }
  
 	//spider position
   	set_spider_pos(graph,spider,rect_spider);

  	//insect position
  	set_insect_pos(graph,insect,rect_insect);

  	//fish_hook position
  	set_fish_hook_pos(graph,fish_hook,rect_fish_hook);

  	////////////painting nodes on screen///////////////////////  
  	painting_nodes_on_screen(graph, rect_circle, circle);

	///////////painting arcs on screen//////////////////////////////

  	if (level_counter == 1)
    	painting_arcs_on_screen(graph, rect_arc, arc3);

  	if (level_counter == 2)
    	painting_arcs_on_screen2(graph, rect_arc, arc3);

  	if (level_counter == 3)
    	painting_arcs_on_screen3(graph, rect_arc, arc3);

  	////////////////////////////REFRESH///////////////////////////
  	SDL_BlitSurface(background, NULL, screen, NULL);
  	BlitSurface_bandw_icon(screen, rect_fire0, rect_glue0, rect_ant0, rect_ice0, rect_right0,fire_bandw,
                       	  glue_bandw,ant_bandw,ice_bandw,right_bandw);
  	refresh_arcs(screen, rect_arc, arc3, num_arcs);
  	refresh_node(screen,rect_circle, circle, n);
  	refresh_insect(screen,rect_insect,insect,num_insect);
  	SDL_BlitSurface(spider, NULL, screen, &rect_spider);
  	//if(rect_fish_hook.x != 0 and rect_fish_hook.y != 0)
  	  SDL_BlitSurface(fish_hook, NULL, screen, &rect_fish_hook);
  	SDL_Flip(screen);


 	while (continue_game == true and exist_path == true)
  	{
   		/////////////////Detecting which one power is activated////////////////////
   		if (powers[0] >= 1)
     		fire_bandw = load_IMG_fire(0);
   		if(powers[0] == 0)
      		fire_bandw = load_IMG_fire(1);

    	if (powers[1] >= 1)
      		glue_bandw = load_IMG_glue(0);
    	if(powers[1] == 0)
     		glue_bandw = load_IMG_glue(1);

    	if (powers[2] >= 1)
      		ice_bandw = load_IMG_ice(0);
    	if(powers[2] == 0)
      	ice_bandw = load_IMG_ice(1);

    	if (powers[3] >= 1)
      		ant_bandw = load_IMG_ant(0);
    	if(powers[3] == 0)
      		ant_bandw = load_IMG_ant(1);

    	if (powers[4] >= 1)
      		right_bandw = load_IMG_right(0);
    	if(powers[4] == 0)
      		right_bandw = load_IMG_right(1);

      	SDL_BlitSurface(background, NULL, screen, NULL);
      	BlitSurface_bandw_icon(screen, rect_fire0, rect_glue0, rect_ant0, rect_ice0, rect_right0,fire_bandw,
             	               glue_bandw,ant_bandw,ice_bandw,right_bandw);
     	refresh_arcs(screen, rect_arc, arc3, num_arcs);
      	refresh_node(screen,rect_circle, circle, n);
      	refresh_insect(screen,rect_insect,insect,num_insect);
      	SDL_BlitSurface(spider, NULL, screen, &rect_spider);

      	if(rect_fish_hook.x != 0 and rect_fish_hook.y != 0)
        	SDL_BlitSurface(fish_hook, NULL, screen, &rect_fish_hook);

      	SDL_Flip(screen);

		///////////////REMOVE ARC//////////////////////////////////////////////////////////////////
    	while (SDL_PollEvent(&event))
    	{  
      		if(event.type == SDL_QUIT)
    		{
    	  		SDL_Quit();
    	  		exit (0);
    		}

      		SDL_GetMouseState(&mousex, &mousey);
            
      		if(event.type == SDL_MOUSEBUTTONDOWN)
      		{
        		SDL_GetMouseState(&aux_mousex, &aux_mousey);

        		if (event.button.button ==  SDL_BUTTON_LEFT)
        		{
          			for (GT::Arc_Iterator it(graph); it.has_curr();  )
          			{
         				auto a = it.get_curr();
          				auto u = graph.get_src_node(a);
          				auto v = graph.get_tgt_node(a);
          				Point uu(get<2>(u->get_info()), get<3>(u->get_info()));
          				Point vv(get<2>(v->get_info()), get<3>(v->get_info()));
          				Segment uuvv(uu, vv);

          				Point tl(mousex - 15, mousey - 20);
          				Point tr(mousex, mousey - 20);
          				Point bl(mousex - 15, mousey);
          				Point br(mousex, mousey);

          				it.next();

          				if (uuvv.intersects_with(Segment(tl, tr)) or uuvv.intersects_with(Segment(tl, bl)) or 
          				uuvv.intersects_with(Segment(bl, br)) or uuvv.intersects_with(Segment(tr, br)))
          				{
          					graph.remove_arc(a);
          					break;
          				}

      		          	if (mousex >= rect_glue0.x and mousex <= rect_glue0.x + rect_glue0.w 
      			        	and mousey >= rect_glue0.y and rect_glue0.y + rect_glue0.h and powers[1] >= 1)
      		          	{
      		          		exist_power = 2;
      		          		powers[exist_power-1] = powers[exist_power-1]-1;
      		          	}

      		          	if (mousex >= rect_ice0.x and mousex <= rect_ice0.x + rect_ice0.w 
      			        	and mousey >= rect_ice0.y and rect_ice0.y + rect_ice0.h and powers[2] >= 1)
      		          	{
      		          		exist_power = 3;
      		          		powers[exist_power-1] = powers[exist_power-1]-1;
      		          	}

      		          	if (mousex >= rect_fire0.x and mousex <= rect_fire0.x + rect_fire0.w 
      			        	and mousey >= rect_fire0.y and rect_fire0.y + rect_fire0.h and powers[0] >= 1)
      		          	{
 			          		exist_power = 1;
		      				powers[exist_power-1] = powers[exist_power-1]-1;

      		          		while(fire_power == true)
      		          		{

								while (SDL_PollEvent(&event))
    							{  
    								if(event.type == SDL_QUIT)
    								{
    	  								SDL_Quit();
    	  								exit (0);
    								}

      								SDL_GetMouseState(&mousex, &mousey);
            
      								if(event.type == SDL_MOUSEBUTTONDOWN)
      								{ 
        								SDL_GetMouseState(&aux_mousex, &aux_mousey);

        								if (event.button.button ==  SDL_BUTTON_LEFT)
        								{ 
         									for (GT::Node_Iterator it(graph); it.has_curr();  )
          									{
         										auto a = it.get_curr();
         										int Pos_x = get<2>(a->get_info());
         										int Pos_y = get<3>(a->get_info());

          										Point ctl(Pos_x, Pos_y);
          										Point ctr(Pos_x + 30, Pos_y);
          										Point cbl(Pos_x, Pos_y + 27);
          										Point cbr(Pos_x + 30, Pos_y+ 27);

          										Segment ctlctr(ctl, ctr);
          										Segment ctlcbl(ctl, cbl);
          										Segment ctrcbr(ctr, cbr);
          										Segment cblcbr(cbl, cbr);

          										Point tl(mousex - 15, mousey - 20);
          										Point tr(mousex, mousey - 20);
          										Point bl(mousex - 15, mousey);
          										Point br(mousex, mousey);

          										it.next();

          										if (ctlctr.intersects_with(Segment(tl, tr)) or ctlctr.intersects_with(Segment(tl, bl)) or 
          										ctlctr.intersects_with(Segment(bl, br)) or ctlctr.intersects_with(Segment(tr, br)) or
          										ctlcbl.intersects_with(Segment(tl, tr)) or ctlcbl.intersects_with(Segment(tl, bl)) or 
          										ctlcbl.intersects_with(Segment(bl, br)) or ctlcbl.intersects_with(Segment(tr, br)) or
          										ctrcbr.intersects_with(Segment(tl, tr)) or ctrcbr.intersects_with(Segment(tl, bl)) or 
          										ctrcbr.intersects_with(Segment(bl, br)) or ctrcbr.intersects_with(Segment(tr, br)) or
           										cblcbr.intersects_with(Segment(tl, tr)) or cblcbr.intersects_with(Segment(tl, bl)) or 
          										cblcbr.intersects_with(Segment(bl, br)) or cblcbr.intersects_with(Segment(tr, br)))
          										{

          											graph.remove_node(a);
          											fire_power = false;
          											break;

          										}
											}	
										}
									}
    							}
      		          		}
      		      break;}

      		          	if (mousex >= rect_ant0.x and mousex <= rect_ant0.x + rect_ant0.w 
      			        	and mousey >= rect_ant0.y and rect_ant0.y + rect_ant0.h and powers[3] >= 1)
      		          	{ 
 			          		exist_power = 3;
		      				powers[exist_power-1] = powers[exist_power-1]-1;

      		          		while(ant_power == true)
      		          		{

								while (SDL_PollEvent(&event))
    							{  
    								if(event.type == SDL_QUIT)
    								{
    	  								SDL_Quit();
    	  								exit (0);
    								}

      								SDL_GetMouseState(&mousex, &mousey);

      								if(event.type == SDL_MOUSEBUTTONDOWN)
      								{ 
        								SDL_GetMouseState(&aux_mousex, &aux_mousey);

        								if (event.button.button ==  SDL_BUTTON_LEFT)
        								{ 
         									for (GT::Node_Iterator it(graph); it.has_curr();  )
          									{       
         										auto a = it.get_curr();
         										int Pos_x = get<2>(a->get_info());
         										int Pos_y = get<3>(a->get_info());

          										Point ctl(Pos_x, Pos_y);
          										Point ctr(Pos_x + 30, Pos_y);
          										Point cbl(Pos_x, Pos_y + 27);
          										Point cbr(Pos_x + 30, Pos_y+ 27);

          										Segment ctlctr(ctl, ctr);
          										Segment ctlcbl(ctl, cbl);
          										Segment ctrcbr(ctr, cbr);
          										Segment cblcbr(cbl, cbr);

          										Point tl(mousex - 15, mousey - 20);
          										Point tr(mousex, mousey - 20);
          										Point bl(mousex - 15, mousey);
          										Point br(mousex, mousey);

          										it.next();

          										if (ctlctr.intersects_with(Segment(tl, tr)) or ctlctr.intersects_with(Segment(tl, bl)) or 
          										ctlctr.intersects_with(Segment(bl, br)) or ctlctr.intersects_with(Segment(tr, br)) or
          										ctlcbl.intersects_with(Segment(tl, tr)) or ctlcbl.intersects_with(Segment(tl, bl)) or 
          										ctlcbl.intersects_with(Segment(bl, br)) or ctlcbl.intersects_with(Segment(tr, br)) or
          										ctrcbr.intersects_with(Segment(tl, tr)) or ctrcbr.intersects_with(Segment(tl, bl)) or 
          										ctrcbr.intersects_with(Segment(bl, br)) or ctrcbr.intersects_with(Segment(tr, br)) or
           										cblcbr.intersects_with(Segment(tl, tr)) or cblcbr.intersects_with(Segment(tl, bl)) or 
          										cblcbr.intersects_with(Segment(bl, br)) or cblcbr.intersects_with(Segment(tr, br)))
          										{
          											get<1>(a->get_info()) = FISH_HOOK;
          											set_fish_hook_pos(graph,fish_hook,rect_fish_hook);

          											ant_power = false;
          											break;

          										}
											}	
										}
									}
    							}
      		          		}
      		      break;} 



      		          	if (mousex >= rect_right0.x and mousex <= rect_right0.x + rect_right0.w 
      			        	and mousey >= rect_right0.y and rect_right0.y + rect_right0.h and powers[4] >= 1)
      		          	{ 
 			          		exist_power = 4;
		      				powers[exist_power-1] = powers[exist_power-1]-1;

      		          		while(right_power == true)
      		          		{

								while (SDL_PollEvent(&event))
    							{  
    								if(event.type == SDL_QUIT)
    								{
    	  								SDL_Quit();
    	  								exit (0);
    								}

      								SDL_GetMouseState(&mousex, &mousey);

      								if(event.type == SDL_MOUSEBUTTONDOWN)
      								{ 
        								SDL_GetMouseState(&aux_mousex, &aux_mousey);

        								if (event.button.button ==  SDL_BUTTON_LEFT)
        								{ 
         									for (GT::Node_Iterator it(graph); it.has_curr();  )
          									{       
         										auto a = it.get_curr();
         										int Pos_x = get<2>(a->get_info());
         										int Pos_y = get<3>(a->get_info());

          										Point ctl(Pos_x, Pos_y);
          										Point ctr(Pos_x + 30, Pos_y);
          										Point cbl(Pos_x, Pos_y + 27);
          										Point cbr(Pos_x + 30, Pos_y+ 27);

          										Segment ctlctr(ctl, ctr);
          										Segment ctlcbl(ctl, cbl);
          										Segment ctrcbr(ctr, cbr);
          										Segment cblcbr(cbl, cbr);

          										Point tl(mousex - 15, mousey - 20);
          										Point tr(mousex, mousey - 20);
          										Point bl(mousex - 15, mousey);
          										Point br(mousex, mousey);

          										it.next();

          										if (ctlctr.intersects_with(Segment(tl, tr)) or ctlctr.intersects_with(Segment(tl, bl)) or 
          										ctlctr.intersects_with(Segment(bl, br)) or ctlctr.intersects_with(Segment(tr, br)) or
          										ctlcbl.intersects_with(Segment(tl, tr)) or ctlcbl.intersects_with(Segment(tl, bl)) or 
          										ctlcbl.intersects_with(Segment(bl, br)) or ctlcbl.intersects_with(Segment(tr, br)) or
          										ctrcbr.intersects_with(Segment(tl, tr)) or ctrcbr.intersects_with(Segment(tl, bl)) or 
          										ctrcbr.intersects_with(Segment(bl, br)) or ctrcbr.intersects_with(Segment(tr, br)) or
           										cblcbr.intersects_with(Segment(tl, tr)) or cblcbr.intersects_with(Segment(tl, bl)) or 
          										cblcbr.intersects_with(Segment(bl, br)) or cblcbr.intersects_with(Segment(tr, br)))
          										{
          											string aux_insect = posicion_insect(graph);

          											graph.for_each_node([&](auto a)
          											{ 
          												if(get<0>(a->get_info()) == aux_insect)
          													get<1>(a->get_info()) = EMPTY;
          											});

          											get<1>(a->get_info()) = INSECT;
          											set_insect_pos(graph,insect,rect_insect);
          											right_power= false;
          											break;

          										}
											}	
										}
									}
    							}
      		          		}
      		      break;} 

         			}  

          			aux_num_arcs = graph.get_num_arcs();
        		}
    		}	
		}

       	if(aux_num_arcs < num_arcs)
       	{ 	
      		if (level_counter == 1)
      	  		painting_arcs_on_screen(graph, rect_arc, arc3);    
 			if (level_counter == 2)
   		  		painting_arcs_on_screen2(graph, rect_arc, arc3);
   			if (level_counter == 3)
          		painting_arcs_on_screen3(graph, rect_arc, arc3);

      		SDL_BlitSurface(background, NULL, screen, NULL);
        	BlitSurface_bandw_icon(screen, rect_fire0, rect_glue0, rect_ant0, rect_ice0, rect_right0,fire_bandw,
        	glue_bandw,ant_bandw,ice_bandw,right_bandw);
       		refresh_arcs(screen, rect_arc, arc3, num_arcs);
        	refresh_node(screen,rect_circle, circle, n);
        	refresh_insect(screen,rect_insect,insect,num_insect);
        	SDL_BlitSurface(spider, NULL, screen, &rect_spider);
        	

        	if(rect_fish_hook.x != 0 and rect_fish_hook.y != 0)
          		SDL_BlitSurface(fish_hook, NULL, screen, &rect_fish_hook);

        	SDL_Flip(screen);

      		aux_spider = posicion_spider(graph);
      		aux_fish_insect = posicion_insect(graph);

      		if(num_insect > 1)
      			aux_fish_insect_2 = posicion_insect_2(graph, aux_fish_insect);

      		aux_fish_hook = posicion_fish_hook(graph);

      		auto path = Finding_Path(graph, aux_spider, aux_fish_insect);
      		auto path_fish_hook = Finding_Path(graph, aux_spider, aux_fish_hook);
      		auto path_2 = Finding_Path(graph, aux_spider, aux_fish_insect_2);

      		if(path.is_empty() and path_2.is_empty())
      		{
        		exist_path = false;
        		cout << "   --- COMPLETE LEVEL: " << level_counter <<" ---"<<endl << endl;
        		level_counter++;

        		Select_level(graph, level_counter);

        		play(graph);
        		//break;
      		}

      		if(exist_path == true)
      		{
      			///////////SPIDER WALKING////////////////
        		if(exist_power != 2)            ///////////////power GLUE/////////////
        		{
      				nodo_aux = path.get_first_node(); 
       				path.remove_first_node();
          			nodo_aux2 = path.get_first_node(); 

          			nodo_aux_hook = path_fish_hook.get_first_node(); 
          			path_fish_hook.remove_first_node();
          			nodo_aux2_hook = path_fish_hook.get_first_node(); 

       				nodo_aux_insect_2 = path_2.get_first_node();
       				path_2.remove_first_node();
       				nodo_aux2_insect_2 = path_2.get_first_node(); 
          			

		  			if(not (get<0>(nodo_aux2->get_info()) == aux_fish_insect and exist_power == 3))   //////////power ICE/////////////
		  			{

		    			if(path_fish_hook.size() < path.size() and path_fish_hook.is_empty() == false)   ////////power fisk_hook////
		    			{    
              				graph.for_each_node([&](const auto variable)
              				{
              					if (nodo_aux_hook == variable)
                					get<1>(variable->get_info()) = EMPTY;

              					if(nodo_aux2_hook == variable)
                					get<1>(variable->get_info()) = SPIDER;   
              				});	

              				moving_spider_on_screen(nodo_aux_hook, nodo_aux2_hook, rect_insect, rect_spider, spider, insect, background, screen, 
                             	      				 rect_fire0, rect_glue0, rect_ant0, rect_ice0, rect_right0,fire_bandw, glue_bandw,
                             	      				 ant_bandw,ice_bandw,right_bandw, rect_arc, arc3, num_arcs, rect_circle, circle, n,num_insect);

              				set_spider_pos(graph,spider,rect_spider);

              				SDL_BlitSurface(background, NULL, screen, NULL);
              				BlitSurface_bandw_icon(screen, rect_fire0, rect_glue0, rect_ant0, rect_ice0, rect_right0,fire_bandw,
                        	           			 glue_bandw,ant_bandw,ice_bandw,right_bandw);
              				refresh_arcs(screen, rect_arc, arc3, num_arcs);
              				refresh_node(screen,rect_circle, circle, n);
              				refresh_insect(screen,rect_insect,insect,num_insect);
              				SDL_BlitSurface(spider, NULL, screen, &rect_spider);
              				SDL_BlitSurface(fish_hook, NULL, screen, &rect_fish_hook);

						}

						else
						{	   

              					graph.for_each_node([&](const auto variable)
              					{
                					if (nodo_aux == variable)
                  						get<1>(variable->get_info()) = EMPTY;

                					if(nodo_aux2 == variable)
                  						get<1>(variable->get_info()) = SPIDER;   
              					});

              					moving_spider_on_screen(nodo_aux, nodo_aux2, rect_insect, rect_spider, spider, insect, background, screen, 
                            	 	      				rect_fire0, rect_glue0, rect_ant0, rect_ice0, rect_right0,fire_bandw, glue_bandw,
                             		      				ant_bandw,ice_bandw,right_bandw, rect_arc, arc3, num_arcs, rect_circle, circle, n,num_insect);

              					set_spider_pos(graph,spider,rect_spider);

              					SDL_BlitSurface(background, NULL, screen, NULL);
              					BlitSurface_bandw_icon(screen, rect_fire0, rect_glue0, rect_ant0, rect_ice0, rect_right0,fire_bandw,
              					                       glue_bandw,ant_bandw,ice_bandw,right_bandw);
              					refresh_arcs(screen, rect_arc, arc3, num_arcs);
              					refresh_node(screen,rect_circle, circle, n);
              					refresh_insect(screen,rect_insect,insect,num_insect);
              					SDL_BlitSurface(spider, NULL, screen, &rect_spider);
              					SDL_BlitSurface(fish_hook, NULL, screen, &rect_fish_hook);

            			}
        			}
      			}

       			/////////////GAME OVER???////////////
       			is_game_over(graph, aux_fish_insect, aux_fish_insect_2); 

   				if (continue_game == false)
       			{
       				SDL_Surface * game_over = SDL_LoadBMP("img/gameover.bmp");
       				SDL_Rect rect_go, rect_exit, rect_play0;
        			SDL_Surface *exit0 = IMG_Load("img/png/exit.png");
         
         			if (game_over== NULL)
         			{
         			  cout << "ERROR: " << SDL_GetError() << endl;
         			}

         			if (exit0== NULL)
         			{
         			  cout << "ERROR: " << SDL_GetError() << endl;
         			}

          			rect_go.x = WIDTH/2 - game_over->w/2;
          			rect_go.y = HEIGHT/2 - game_over->h/2;

          			rect_exit.x = WIDTH/2 + WIDTH/5;
          			rect_exit.y = HEIGHT/2 + HEIGHT/4;

          			rect_play0.x = WIDTH/4;
          			rect_play0.y = HEIGHT/2 + HEIGHT/4;


          			//game over
          			SDL_FreeSurface(screen);
          			SDL_BlitSurface(game_over, NULL, screen, &rect_go);
          			SDL_BlitSurface(exit0, NULL, screen, &rect_exit);
          			SDL_Flip(screen);

          			bool answ = true;

					while(answ)
       				{
          				SDL_GetMouseState(&mousex,&mousey);
						
          				while(SDL_PollEvent(&event))
          				{
            	  			if(event.type == SDL_QUIT)
            	  			{
            	  			    SDL_Quit();
              				    exit (0);
              				 }
  	
            				SDL_GetMouseState(&mousex, &mousey);

            				if(event.type == SDL_MOUSEBUTTONDOWN)
            				{
            				 	SDL_GetMouseState(&aux_mousex, &aux_mousey);
	
            					if (event.button.button ==  SDL_BUTTON_LEFT)
            					{
            					    if (mousex >= rect_exit.x and mousex <= rect_exit.x + rect_exit.w 
            					        and mousey >= rect_exit.y and mousey <= rect_exit.y + rect_exit.h)
            				        {
            					  	    SDL_Quit();
            						    exit(0);
            					   	    answ = false;
            				        }
              					}
            				}	
          				}
       		   		}
      			}   

        		if(aux_num_arcs < num_arcs)
          			play(graph);
    		} 
      	}
  	}

  	return;
}