#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <random>
#include <QGraphicsRectItem>
#include <vector>
#include <map>
#include <QTimer>
#include <time.h>
#include <QKeyEvent>

/*
 * name: Vesa Haaparanta
 * email: vesa.haaparanta@tuni.fi
 * student id: 290336
*/

class Tetrixpiece
{
public:
    Tetrixpiece(QGraphicsRectItem* piece, int coordinate_x, int coordinate_y);
    ~Tetrixpiece();
    QGraphicsRectItem* returnPointer();
    int position_on_x();
    int position_on_y();
    int exact_position();
    void moving_piece(char heading);
    void setX(int new_X);
    void setY(int new_Y);
    void moveby(int deltax, int deltay);
    
private:
    const int STEP = 20;

    QGraphicsRectItem* piece_;
    int coordinate_x_;
    int coordinate_y_;


};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event) override;
    bool paused_ = true;

private slots:
     void on_start_button_clicked();

     void on_pause_button_clicked();

     void on_reset_button_clicked();

     void on_quit_button_clicked();

     void on_continue_button_clicked();

     void on_crazy_radio_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene_;

    // Constants describing scene coordinates
    // Copied from moving circle example and modified a bit
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 480; // 260; (in moving circle)
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 240; // 680; (in moving circle)

    // Size of a tetromino component
    const int SQUARE_SIDE = 20;
    const qreal STEP = 20;
    // Number of horizontal cells (places for tetromino components)
    const int COLUMNS = BORDER_RIGHT / SQUARE_SIDE;
    // Number of vertical cells (places for tetromino components)
    const int ROWS = BORDER_DOWN / SQUARE_SIDE;

    // Constants for different tetrominos and the number of them
    enum Tetromino_kind {HORIZONTAL,
                         LEFT_CORNER,
                         RIGHT_CORNER,
                         SQUARE,
                         STEP_UP_RIGHT,
                         PYRAMID,
                         STEP_UP_LEFT,
                         NUMBER_OF_TETROMINOS};
    // From the enum values above, only the last one is needed in this template.
    // Recall from enum type that the value of the first enumerated value is 0,
    // the second is 1, and so on.
    // Therefore the value of the last one is 7 at the moment.
    // Remove those tetromino kinds above that you do not implement,
    // whereupon the value of NUMBER_OF_TETROMINOS changes, too.
    // You can also remove all the other values, if you do not need them,
    // but most probably you need a constant value for NUMBER_OF_TETROMINOS.


    // For randomly selecting the next dropping tetromino
    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> distr;

    // More constants, attibutes, and methods
    QTimer lap_time_;
    int seconds_;
    int score_;

    QTimer timer_;
    int game_speed; // game speed. which sppeds up while playing.

    const int multiplier = 1000;

    int twisting_value_;
    char heading_;
    std::vector<Tetrixpiece*> next_;
    std::vector<Tetrixpiece*> current_;
    // key is y*1000+x, used to keep track of the pointers.
    std::map<int, Tetrixpiece*> map_of_tetris_;

    void tetrimino_move();
    bool is_movable(char heading);
    void tetrimino_make_new();
    void add_current();
    bool twisting();
    bool game_is_lost();
    void clear_board();
    void update_seconds();
    bool remove_full_lines();
    bool if_full_line(int line);
    void gravity();
    void gravity_move_down(Tetrixpiece* piece);
    void move_down();

};
#endif // MAINWINDOW_HH
