
////////GAME: GREEDY SPIDERS BY GREEDY SQUAD//////////////

////////////NODE STATUS//////////////////////
enum Status_spider
{
  SPIDER,
  EMPTY,
  INSECT
};

using Nodes = pair<char, Status_spider>;
using Node = Graph_Node<Nodes>;
using GT = List_Graph<Node>;

struct WriteNode
{
  string operator () (GT::Node * p)
  {
    stringstream s, s1;
    if (get<1>(p->get_info()) == 0)
    {
      s1 << "-S";
    }
    else if (get<1>(p->get_info()) == 2)
    {
      s1 << "-I";
    }
       s << get<0>(p->get_info());       

    return s.str()+s1.str();
  }
};

struct WriteArc
{
  string operator () (GT::Arc *)
  {
    return "";
  }
};

///////////Print a Graph//////////////////////////////////////
void Generate_Graph(GT graph)
{

  //Generate graph - archivo .dot 
  ofstream output("greedySpiders.dot");

    if (not output)
    {
      cout << "Error creating greedySpiders.dot\n";
      return ;
    }

  Generate_Graphviz<GT, WriteNode, WriteArc>()(graph, output, "LR");

  output.close();

  system("dot -Tpng greedySpiders.dot -o greedySpiders.png");
}

///////////Build_Graph////////////////////////////////////
void Build_Graph(GT &graph)
{
  
  auto A = graph.insert_node(make_pair('A',SPIDER));
  auto B = graph.insert_node(make_pair('B',EMPTY));
  auto C = graph.insert_node(make_pair('C',EMPTY));
  auto D = graph.insert_node(make_pair('D',EMPTY));
  auto E = graph.insert_node(make_pair('E',EMPTY));
  auto F = graph.insert_node(make_pair('F',INSECT));
  
  graph.insert_arc(A, B);
  graph.insert_arc(A, C);
  graph.insert_arc(A, D);
  graph.insert_arc(B, E);
  graph.insert_arc(C, E);
  graph.insert_arc(D, E);
  graph.insert_arc(B, C);
  graph.insert_arc(C, D);
  graph.insert_arc(E, F);

  cout << "          GAME: GREEDY SPIDERS BY GREEDY SQUAD" << endl;
  cout << endl << "       LEVEL 1" ;
  cout << endl << "Init. Node - Spider: A" << "  , "<< "Insect Position: F"  << endl << endl;

}

///////////Build_Graph2////////////////////////////////////
void Build_Graph2(GT &graph)
{
  
  auto A = graph.insert_node(make_pair('A',EMPTY));
  auto B = graph.insert_node(make_pair('B',EMPTY));
  auto C = graph.insert_node(make_pair('C',EMPTY));
  auto D = graph.insert_node(make_pair('D',SPIDER));
  auto E = graph.insert_node(make_pair('E',EMPTY));
  auto F = graph.insert_node(make_pair('F',EMPTY));
  auto G = graph.insert_node(make_pair('G',INSECT));

  graph.insert_arc(A, B);
  graph.insert_arc(A, C);
  graph.insert_arc(A, D);
  graph.insert_arc(B, C);
  graph.insert_arc(C, D);
  graph.insert_arc(B, E);
  graph.insert_arc(B, G);
  graph.insert_arc(C, E);
  graph.insert_arc(D, F);
  graph.insert_arc(E, F);
  graph.insert_arc(E, G);
  graph.insert_arc(F, G);

  cout << endl << "       LEVEL 2";
  cout << endl << "Init. Node - Spider: D" << "  , "<< "Insect Position: G"  << endl << endl;
}

///////////SELECT LEVEL/////////////////////////////////////
bool exist_path = true;

void Select_level(GT &graph ,int level)
{
  clear_graph(graph);

    switch (level)
    {
      case 2:  
        Build_Graph2(graph);
        exist_path = true;
        break;
     
      default: 
        return;
    }
} 

///////////Remove Arc/////////////////////////////
Graph_Arc<unsigned long> * Remove_arc_graph(GT &graph)
{
  cout<< endl << "Insert Arc you wanna remove:" <<endl;
  
  char find_A, find_B;
  Node *Nodo_A, *Nodo_B;

  cin >> find_A;
  cin >> find_B;

    graph.for_each_node([&](const auto aux)
    {
      if (get<0>(aux->get_info()) == find_A)
        Nodo_A = aux;

      if (get<0>(aux->get_info()) == find_B)
        Nodo_B = aux;
    });

  Graph_Arc<unsigned long> * remove_arc = graph.search_arc(Nodo_A,Nodo_B);
  graph.remove_arc(remove_arc);

  return remove_arc;
}

//////// Find Path////////////////////////////////////
Path<GT > Finding_Path(GT &graph, char aux_start, char aux_end)
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

    cout << "Spider-insect Path: " << endl;

    if(!path.is_empty())
    {
      path.for_each_node([&](const auto aux)
      {
        cout << get<0>(aux->get_info()) << ",";
      });
    }

    if(path.is_empty())
      cout << "THERE'S NO PATH"<<endl;

  return path;
}


//////////////////PLAY//////////////////////////////////////////
bool continue_game = true;
int level_counter = 1;

void play(GT &graph)
{
  char aux_caracter, aux_caracter2;
  Node * nodo_aux , * nodo_aux2;
  Generate_Graph(graph);
  system("eog greedySpiders.png &");

    while (continue_game == true and exist_path == true)
    {
      Remove_arc_graph(graph);
      system("clear"); 
      cout << "          GAME: GREEDY SPIDERS BY GREEDY SQUAD" << endl << endl;

      cout << "Arc has been removed" << endl;

      graph.for_each_node([&](const auto aux)
      {
        if (get<1>(aux->get_info()) == SPIDER)
          aux_caracter = get<0>(aux->get_info());

        if (get<1>(aux->get_info()) == INSECT)
          aux_caracter2 = get<0>(aux->get_info());;
      });

      auto path = Finding_Path(graph, aux_caracter, aux_caracter2);

      if(path.is_empty())
      {
        exist_path = false;
        cout << "   --- YOU WIN LEVEL COMPLETED: " << level_counter <<" ---"<<endl << endl;
        level_counter++;

        Select_level(graph, level_counter);

        play(graph);
        break;
      }

      if(exist_path == true)
      {
        nodo_aux = path.get_first_node(); 
        path.remove_first_node();
        nodo_aux2 = path.get_first_node(); 
        aux_caracter = get<0>(nodo_aux2->get_info());

        cout <<  endl << "Spider Position:"  <<  aux_caracter << endl << "INSECT en nodo:" << aux_caracter2 << endl;
  
        graph.for_each_node([&](const auto variable)
        {
          if (nodo_aux == variable)
            get<1>(variable->get_info()) = EMPTY;

          if(nodo_aux2 == variable)
            get<1>(variable->get_info()) = SPIDER;   
        });

        graph.for_each_node([&](const auto variable)
        {
          if (get<0>(variable->get_info()) == aux_caracter2)
          {
            if (get<1>(variable->get_info()) == SPIDER)
            {
              continue_game = false;
              Generate_Graph(graph);
              cout << "   ---GAME OVER---  " << endl<< endl;   
            }
          }

        });
        
        play(graph);
      } 
    
    }

  return;
}