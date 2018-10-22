#include "../include/Level.hpp"
#include "../include/World.hpp"

using namespace std;

Level::Level()
{
    currentId = 0;
    m_hauteur = 1;
    m_largeur = 1;
    m_taille = m_hauteur*m_largeur;
    m_nomMap = "";
}

void Level::init(World *t_world, int const largeur, int const hauteur, string nomMap, int const state)
{
    m_world = t_world;
    m_entityStdStorage.init(m_world->getGlobalSys());
    m_hauteur = hauteur;
    m_largeur = largeur;
    m_taille = hauteur*largeur;
    m_nomMap = nomMap;
    m_divisionRegion = 256;
    sf::Clock clock;
    if(state==1)
        create();
    else if (state == 0)
        loadLevel();
//init de l'entity avec l'id 0 de type error
    int posInEntityVector = m_entityArray.size();
    m_entityArray.emplace_back();
    m_entityArray[m_entityArray.size()-1] =  new Entity(m_world, m_world->getGlobalSys());
    *m_entityArray[m_entityArray.size()-1] =  m_entityStdStorage.getEntityCpy(entType::last); //remplcaer player par last quand le type error existe
    m_entityArrayIndex[currentId] = posInEntityVector;
    currentId++;
    getEntityById(0)->setName("entityError");
    getEntityById(0)->setId(0);
}

int Level::addEntity(entType type)
{
    int posInEntityVector;
    if (m_entityArrayFreeSpace.empty() == true)
    {
        posInEntityVector = m_entityArray.size();
        m_entityArray.emplace_back();
//        m_entityArray[m_entityArray.size()-1] = (Entity*) malloc(m_entityStdStorage.getEntitySize(type)); //cette ligne est cencé etre valide mais ca fait crashe,r du coup j'ai tulier une techniqu_e de gitan pour palier au probleme, instabilité de l'os a prevoir
        m_entityArray[m_entityArray.size()-1] =  new Entity(m_world, m_world->getGlobalSys());
        *m_entityArray[m_entityArray.size()-1] =  m_entityStdStorage.getEntityCpy(type);

    }
    else
    {
        posInEntityVector = m_entityArrayFreeSpace.top();
        m_entityArrayFreeSpace.pop();
        *m_entityArray.at(posInEntityVector) = m_entityStdStorage.getEntityCpy(type);
    }
    m_entityArrayIndex[currentId] = posInEntityVector;
    std::stringstream ss;
    ss << currentId;
    std::string nom = "entityNumero ";
    nom += ss.str();
    //std::cout << "entPos: " << posInEntityVector << "\n";
//    m_entityArray[posInEntityVector]->setName(nom);
    m_entityArray[posInEntityVector]->setId(currentId);
    currentId++;
    return currentId-1;
}
void Level::removeEntity(int id)
{
    m_entityArrayFreeSpace.push(m_entityArrayIndex[id]);
    m_entityArrayIndex.erase(id);
}
Entity* Level::getEntityById(int id)
{
    Entity* tampon;
    tampon = m_entityArray[m_entityArrayIndex[id]];
    //std::cout <<tampon->getId() << " " << id<<std::endl;

    if(tampon->getId() == id)
        return m_entityArray[m_entityArrayIndex[id]];
    else
        return m_entityArray[0];
}
void Level::update()
{
    updateRegion();
}
World* Level::getWorld()
{
    return (m_world);
}
void Level::loadLevel()
{
    double chargement = 0;
    double incrsPerBlock = 100/double(m_largeur*m_hauteur);
    m_regions.resize(m_largeur/m_divisionRegion);
    for(unsigned int i=0; i<m_regions.size(); i++)
        m_regions[i].resize(m_hauteur/m_divisionRegion);
    m_nombreRegions = 0;
    vector<vector<int> > currentRegion;
    currentRegion.resize(m_divisionRegion);
    for(unsigned int i=0; i<currentRegion.size(); i++)
        currentRegion[i].resize(m_divisionRegion);
    for(int x = 0; x<m_largeur/m_divisionRegion; x++)
        for(int y = 0; y<m_hauteur/m_divisionRegion; y++)
        {
            m_regions[x][y] = new Region(this);
            m_regions[x][y]->setIsLoaded(false);
            m_regions[x][y]->setPos(sf::Vector2i(x,y));
            m_nombreRegions++;
            ostringstream convPathFichier;
            convPathFichier << "maps\\" << m_nomMap << "\\région" << x << "-" << y << ".map"; // conversion du j en string
            string newPathFichier;
            newPathFichier = convPathFichier.str();
            ifstream maps;
            maps.open(newPathFichier.c_str());
            if(maps)
            {
                for(int a = 0; a < m_divisionRegion; a++)
                {
                    for (int b = 0; b < m_divisionRegion; b++)
                    {
                        chargement += incrsPerBlock;
                        int tile;
                        maps >> tile;
                        currentRegion[a][b] = tile;
                        if(a%50==0 && b==0) cout<<chargement<<"%  - Load de la map"<<endl;
                    }
                }
                maps.close();
                m_regions[x][y]->setBlocks(currentRegion);
            }
            else
            {
                cout << "Impossible d'ouvrir la map !"<<endl;
                cout << "Creation d'une nouvelle map !"<<endl;
                create();
            }
        }
    m_world->getPerso()->load(m_nomMap);
    cout<<"100% - Load complete"<<endl;
}

void Level::save()
{
    int division = m_divisionRegion;
    int largeurCourante = division;
    int hauteurCourante = division;
    ofstream maps;
    getVecRegion().x;
    double chargement = 0;
    double incrsPerBlock = 100/double(m_largeur*m_hauteur);
    for (int x = 0; x < getVecRegion().x; x++)
    {
        hauteurCourante = division;
        for(int y = 0; y < getVecRegion().y; y++)
        {
            ostringstream convPathFichier;
            convPathFichier << "maps\\" << m_nomMap << "\\région" << x <<"-"<< y << ".map"; // conversion du j en string
            string newPathFichier;
            newPathFichier = convPathFichier.str();
            maps.open(newPathFichier.c_str());
            if(maps)
            {
                vector<vector<int> > temp = getRegion(sf::Vector2i(x,y))->getBlocks();
                for(int a = 0; a < m_divisionRegion; a++)
                {
                    for(int b = 0; b < m_divisionRegion; b++)
                    {
                        maps <<temp[a][b]<< " ";
                        chargement += incrsPerBlock;
                        if(a%50==0 && b==0)
                            cout<<chargement<<"%  - Sauvegarde de la map"<<endl;
                    }
                    maps <<endl;
                }
            }
            else
            {
                cout << "Impossible de sauvegarder la map !";
            }
            maps.close();
            hauteurCourante += division;
        }
        largeurCourante += division;
    }
    m_world->getPerso()->save(m_nomMap);
    cout<<"100% - Sauvegarde terminee"<<endl;
}
vector<vector<int> > Level::getLevel()
{
    return m_level;
}
void Level::setLevel(int x,int y)
{
    m_level[x][y] = 0;
}
int Level::getSize()
{
    return m_taille;
}
int Level::getHauteur()
{
    return m_hauteur;
}
int Level::getLargeur()
{
    return m_largeur;
}
int Level::getDivision()
{
    return m_divisionRegion;
}
Region* Level::getRegion(sf::Vector2i pos)
{
    return m_regions[pos.x][pos.y];
}
sf::Vector2i Level::getVecRegion()
{
    sf::Vector2i temp;
    temp.x = m_regions.size();
    temp.y = m_regions[0].size();
    return temp;
}

int Level::getRegioSize()
{
    return m_regions.size();
}

void Level::setBlock(sf::Vector2i pos, int type)
{
    pos.x = pos.x/32;
    pos.y = pos.y/32;

    sf::Vector2i regionBlockClicker = sf::Vector2i(pos.x/256,pos.y/256);
    sf::Vector2i blockClicker = sf::Vector2i(pos.x%256,pos.y%256);

    m_regions[regionBlockClicker.x][regionBlockClicker.y]->setBlock(blockClicker, type);
}
int Level::getBlock(sf::Vector2i pos)
{
    pos.x = pos.x/32;
    pos.y = pos.y/32;

    sf::Vector2i regionBlockClicker = sf::Vector2i(pos.x/256,pos.y/256);
    sf::Vector2i blockClicker = sf::Vector2i(pos.x%256, pos.y%256);

    return m_regions[regionBlockClicker.x][regionBlockClicker.y]->getBlock(blockClicker);
}

void Level::create()
{
    //Gestion nom Map + barre chargement

    string pathFichier = "maps\\" + m_nomMap;
    CreateDirectory(pathFichier.c_str(),NULL);
    double chargement = 0;
    double incrsPerBlock = 100/double(m_largeur*m_hauteur);

    //Initialisation de la génération de la map

    srand(time(NULL));

    double tresrare = 1.5;
    double rare = 1.7;
    double normal = 1.9;
    double frequent = 2.0;
    double tresfrequent = 2.1;

    int IDAir = 0;
    int IDDirt = 1;
    int IDStone = 2;
    int IDCoal = 3;
    int IDSilver = 4;

    int IDIron = 6;
    int IDGold = 7;
    int IDDiamond = 8;

    PerlinNoise genereCoal(0.5,0.5,rare,2,rand());
    PerlinNoise genereSilver(0.5,0.5,rare,2,rand());
    PerlinNoise genereIron(0.5,0.5,tresrare,2,rand());
    PerlinNoise genereGold(0.5,0.5,rare,2,rand());
    PerlinNoise genereDiamond(0.5,0.5,rare,2,rand());

    PerlinNoise genereCavern(2,0.15,2,2,rand());

    int coucheMer = 1024;
    int couche1 = coucheMer+256;
    int couche2 = coucheMer+512;
    int couche3 = coucheMer+768;

    int block=IDStone;
    m_level.resize(m_largeur);
    for(unsigned int i=0; i<m_level.size(); i++)
        m_level[i].resize(m_hauteur);
    for(int i=0; i<m_largeur; i++)
    {
        for(int j=0; j<m_hauteur; j++)
        {

            //Reset du minerais

            double coal = 0;
            double silver = 0;
            double iron = 0;
            double gold = 0;
            double diamond = 0;

            double cavern = 0;

            //Reset de la rarete du minerais

            genereCoal.SetAmplitude(rare);
            genereSilver.SetAmplitude(rare);
            genereIron.SetAmplitude(tresrare);
            genereGold.SetAmplitude(rare);
            genereDiamond.SetAmplitude(rare);

            //generation de la surfacem_divisionRegion

            if(j>=coucheMer-20 && j<=coucheMer+20)
            {
                block = IDDirt;
            }

            //Adaptation en fonction de la hauteur de la rarete du minerais

            if(j>coucheMer+20)
            {
                genereCoal.SetAmplitude(normal);
                genereIron.SetAmplitude(rare);
            }
            if(j>couche1)
            {
                genereIron.SetAmplitude(normal);
                genereCoal.SetAmplitude(frequent);
            }
            if(j>couche2)
            {
                genereSilver.SetAmplitude(normal);
                genereIron.SetAmplitude(frequent);
                genereCoal.SetAmplitude(tresfrequent);
            }
            if(j>couche3)
            {
                genereSilver.SetAmplitude(frequent);
                genereGold.SetAmplitude(normal);
                genereIron.SetAmplitude(tresfrequent);
            }

            //generation des minerais

            if(j>coucheMer-20)
            {
                coal = genereCoal.GetHeight(i,j);
                iron = genereIron.GetHeight(i,j);
            }
            if(j>couche1)
            {
                silver = genereSilver.GetHeight(i,j);
                genereIron.SetAmplitude(rare);
            }
            if(j>couche2)
            {
                gold = genereGold.GetHeight(i,j);
            }
            if(j>couche3)
            {
                diamond = genereDiamond.GetHeight(i,j);
            }

            if(j>coucheMer+20)
            {
                cavern = genereCavern.GetHeight(i,j);
            }
            if(coal<=-1)
                block = IDCoal;
            if(iron<=-1)
                block = IDIron;
            if(silver<=-1)
                block = IDSilver;
            if(gold<=-1)
                block = IDGold;
            if(diamond<=-1)
                block = IDDiamond;
            if(cavern<=-1)
                block = IDAir;
            if(coal>-1 && iron>-1 && diamond>-1 && gold>-1 && silver>-1 && cavern>-1 && j>coucheMer+20)
            {
                block = IDStone;
            }
            if(j<coucheMer-20)
                block = IDAir;
            if(cavern<-0.2)
                block = IDAir;
            m_level[i][j]= block;
            chargement += incrsPerBlock;
            if(i%15==0 && j==0)
                cout<<chargement<<"%  - Creation de la map"<<endl;
        }
    }
    cout<<chargement-0.0234<<"%  - Initialisasion des regions"<<endl;
    int largeurCourante = m_divisionRegion;
    int hauteurCourante = m_divisionRegion;
    m_regions.resize(m_largeur/m_divisionRegion);
    for(unsigned int i=0; i<m_regions.size(); i++)
        m_regions[i].resize(m_hauteur/m_divisionRegion);
    m_nombreRegions = 0;
    vector<vector<int> > levelCourant;
    levelCourant.resize(m_divisionRegion);
    for(unsigned int i=0; i<levelCourant.size(); i++)
        levelCourant[i].resize(m_divisionRegion);
    for (int a = 0; a < m_largeur/m_divisionRegion; a++)
    {
        hauteurCourante = m_divisionRegion;
        for(int b = 0; b < m_hauteur/m_divisionRegion; b++)
        {
            m_regions[a][b] = new Region(this);
            m_regions[a][b]->setIsLoaded(false);
            m_regions[a][b]->setPos(sf::Vector2i(a,b));
            m_nombreRegions++;
            int tempI = 0;
            for(int i = largeurCourante - m_divisionRegion; i < largeurCourante; ++i)
            {
                int tempJ = 0;
                for(int j = hauteurCourante - m_divisionRegion; j < hauteurCourante; ++j)
                {
                    levelCourant[tempI][tempJ] = m_level[i][j];
                    tempJ++;
                }
                tempI++;
            }
            m_regions[a][b]->setBlocks(levelCourant);
            m_regions[a][b]->decris();
            hauteurCourante += m_divisionRegion;
        }
        largeurCourante += m_divisionRegion;
    }
    cout<<"100%"<<endl;
    save();
}

void Level::render()
{
    int stackSource;
    if (regionContainer[0].empty())
        stackSource = 1;
    else
        stackSource = 0;
    int stackTarget;
    if (stackSource == 0)
        stackTarget = 1;
    else
        stackTarget = 0;
    while (!regionContainer[stackSource].empty())
    {
        regTampon = regionContainer[stackSource].top();
        regionContainer[stackSource].pop();
        regTampon->render();
        regionContainer[stackTarget].push(regTampon);
    }
}

void Level::updateRegion()
{
    int stackSource;
    if (regionContainer[0].empty())
        stackSource = 1;
    else
        stackSource = 0;
    int stackTarget;
    if (stackSource == 0)
        stackTarget = 1;
    else
        stackTarget = 0;
    while (!regionContainer[stackSource].empty())
    {
        regTampon = regionContainer[stackSource].top();
        regionContainer[stackSource].pop();
        regTampon->update();
        if(!checkForUnload(regTampon->getPos()))
            regionContainer[stackTarget].push(regTampon);
    }
    regionUnloadOrder.clear();
    sf::Vector2i temp;
    while (regionLoadOrder.size() != 0)
    {
        temp = regionLoadOrder.back();
        regionLoadOrder.pop_back();
        regionContainer[stackTarget].push(m_regions[temp.x][temp.y]);
    }
}
bool Level::checkForUnload(sf::Vector2i t_value)
{
    for(int i = 0; i < regionUnloadOrder.size() ; i++)
    {
        if (t_value == regionUnloadOrder[i])
            return (true);
    }
    return (false);
}
void Level::receiveLoadSignal(sf::Vector2i t_value)
{
    regionLoadOrder.push_back(t_value);
}
void Level::receiveUnloadSignal(sf::Vector2i t_value)
{
    regionUnloadOrder.push_back(t_value);
}
