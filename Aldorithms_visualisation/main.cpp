#include <window.hpp>


using namespace std;

float ticks = 0;
bool earlyExit = false;
int algorithmMetod = 0;

int main()
{
    

    // Hides console window. 
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, 0);

    font.loadFromFile("arial.ttf");
    
    visualisation::grid.create(grid_sizes);

    //Create window in fullscreen
    visualisation::window::create_win(true);
    visualisation::window::win->setFramerateLimit(60);
     
    //Initialize all containers for search
    visualisation::initSearch(visualisation::grid);
    visualisation::ui::initUi();
    visualisation::sound::loadAssets();

    //main loop
    while (visualisation::window::win->isOpen())
    {

        visualisation::window::update();

        

        visualisation::render::render();

        //sf::Vector2i mousepos = visualisation::render::mouseOnTile(visualisation::grid);
        //std::cout << "mx:" << mousepos.x * (visualisation::grid.rectSize.x + BORDER_WIDTH )<< " my:" << mousepos.y * (visualisation::grid.rectSize.x + +BORDER_WIDTH) << endl;
        
        //sf::Vector2i mousep = sf::Mouse::getPosition(*visualisation::window::win);
        //std::cout << "pos.x:" << mousep.x << " pos.y:" << mousep.y << endl;

        visualisation::window::win->display();
    }
    return 0;
}



