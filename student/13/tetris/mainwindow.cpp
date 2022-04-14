#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <iostream>

/*
 * name: Vesa Haaparanta
 * email: vesa.haaparanta@tuni.fi
 * student id: 290336
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // We need a graphics scene in which to draw rectangles.
    scene_ = new QGraphicsScene(this);

    // The graphicsView object is placed on the window
    // at the following coordinates, but if you want
    // different placement, you can change their values.
    int left_margin = 100; // x coordinate
    int top_margin = 150; // y coordinate

    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui->graphicsView->setGeometry(left_margin, top_margin,
                                  BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1, because
    // each square of a tetromino is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    // Setting random engine ready for the first real call.
    int seed = time(0); // You can change seed value for testing purposes
    randomEng.seed(seed);
    distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TETROMINOS - 1);
    distr(randomEng); // Wiping out the first random number (which is almost always 0)
    // After the above settings, you can use randomEng to draw the next falling
    // tetromino by calling: distr(randomEng) in a suitable method.

    // Add more initial settings and connect calls, when needed.
    timer_.setSingleShot(false);
    // makes game move forward.
    connect(&timer_, &QTimer::timeout, this, &MainWindow::tetrimino_move);
    connect(&lap_time_, &QTimer::timeout, this, &MainWindow::update_seconds);
    ui->game_over_label->hide();
    ui->continue_button->setDisabled(true);
    ui->pause_button->setDisabled(true);
    ui->start_button->setFocusPolicy(Qt::NoFocus);
    ui->continue_button->setFocusPolicy(Qt::NoFocus);
    ui->pause_button->setFocusPolicy(Qt::NoFocus);
    ui->reset_button->setFocusPolicy(Qt::NoFocus);
    ui->quit_button->setFocusPolicy(Qt::NoFocus);
}

MainWindow::~MainWindow()
{
    clear_board();
    delete ui;
}

// Takes in user commands.
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qreal deltax = 0;
    qreal deltay = 0;
    if (!paused_) {
        if (event->key() == Qt::Key_S) {
            heading_ = 'S';
            while (is_movable(heading_)) {
                tetrimino_move();
            }
        } else if (event->key() == Qt::Key_A) {
            heading_ = 'A';
            deltax -= STEP;
        } else if (event->key() == Qt::Key_D) {
            heading_ = 'D';
            deltax += STEP;
        } /* else if (event->key() == Qt::Key_R) { // rotating is WIP
            heading_ = 'R';
        }
        */
    }
    if (heading_ == 'W' or heading_ == 'A' or heading_ == 'D') {
        if (is_movable(heading_)) {
            for (unsigned int i = 0; i < 4; ++i) {
                Tetrixpiece* piece = current_.at(i);
                QGraphicsRectItem* part = piece->returnPointer();
                part->moveBy(deltax, deltay);
                piece->moving_piece(heading_);
            }
        }
    } /*else if (heading_ == 'R'){
        timer_.stop();
        Tetrixpiece* piece_0 = current_.at(0);
        int value_x = piece_0->position_on_x();
        int value_y = piece_0->position_on_y();
        std::cout << "1." << value_x << value_y << std::endl;
        for (unsigned int i = 0; i < 4; ++i) {
            Tetrixpiece* piece = current_.at(i);
            QGraphicsRectItem* part = piece->returnPointer();
            int delta_x = -(piece->position_on_y() - value_y) + value_x;
            int delta_y = (piece->position_on_x() - value_x) + value_y;
            std::cout << "2." << piece->position_on_x() << piece->position_on_y() << std::endl;
            std::cout << "3."<< delta_x << delta_y << std::endl;
            part->setX(delta_x);
            part->setY(delta_y);
            piece->setX(part->x());
            piece->setY(part->y());
            std::cout << "4." << piece->position_on_x() << piece->position_on_y() << std::endl;
            std::cout << "5." << part->x() << part->y() << std::endl;
        }
        timer_.start(game_speed);
    } */
}

// Make new tetrimino from cast.
void MainWindow::tetrimino_make_new()
{
    int lucky_number = distr(randomEng);
    std::map<int, std::vector<int>> assembly_info = {
        {0, {0,1,2,3}}, {1, {0,12,13,14}}, {2, {2,12,13,14}}, {3, {0,1,12,13}},
        {4, {1,2,12,13}}, {5, {1,12,13,14}}, {6, {0,1,13,14}},
    };
    std::vector<QColor> colors = {
        {Qt::cyan, Qt::darkBlue, Qt::magenta, Qt::yellow, Qt::green, Qt::gray, Qt::red}
    };
    QColor color_of_piece = colors.at(lucky_number);
    std::vector<int> numbers = assembly_info.at(lucky_number);
    for (int location : numbers) {
        QBrush Brush(color_of_piece);
        QPen blackPen(Qt::black);
        blackPen.setWidth(1);
        int x = location % 12;
        int y = location / 12;
        qreal qx = x * SQUARE_SIDE;
        qreal qy = y * SQUARE_SIDE;
        qreal size = 19;
        QGraphicsRectItem* piece = scene_->addRect(
                    qx, qy, size, size, blackPen, Brush);
        Tetrixpiece* part = new Tetrixpiece(
                    piece, x * SQUARE_SIDE, y * SQUARE_SIDE);
        next_.push_back(part);
    }
    twisting_value_ = lucky_number;
    score_ += 1;
}
// So I have next one in game arena and when you call this functio
// it makes next one current and makes new current.
void MainWindow::add_current()
{
    qreal moveByX = 4 * STEP; // move to center part of scene 80 - 120
    qreal moveByY = 0;
    for (int i = 0; i < 4; ++i) {
        Tetrixpiece* piece =next_.at(i);
        QGraphicsRectItem* part = piece->returnPointer();
        for (int j = 0; j < 4; ++j) {
            piece->moving_piece('D');
        }
        part->moveBy(moveByX, moveByY);
        current_.push_back(next_.at(i));
    }
    if (game_speed > 50) {
        game_speed -= 5;
    }
    next_.clear();
    tetrimino_make_new();
}

/* My second attempt to make tetriminos rotatable.
bool MainWindow::twisting()
{
    if (twisting_value_ >= 40) {
        twisting_value_ -= 40;
    } else if (twisting_value_ < 0) {
        twisting_value_ += 40;
    }
    std::map<int, std::vector<int>> assembly_info = {
        {0, {0,1,2,3}}, {10, {0,12,24,36}},
        {20, {0,-1,-2,-3}}, {30, {0,-12,-24,-36}},
        {1, {0,12,13,14}}, {11, {0,-1,-13,-23}},
        {21, {0,-12,-11,-10}}, {31,{0,1,-13,-25}},
        {2, {2,12,13,14}}, {12, {-1,0,11,23}},
        {22, {0,-1,-13,-25}}, {32, {0,-12,-13, -14}},
        {3, {0,1,12,13}}, {13, {0,1,12,13}},
        {23, {0,1,12,13}}, {33, {0,1,12,13}},
        {4, {1,2,12,13}}, {14, {0,-12,1,13}},
        {24, {1,2,12,13}}, {34, {0,-12,1,13}},
        {5, {1,12,13,14}}, {15, {0,-1,-13,11}},
        {25, {0,-11,-12,-13}}, {35, {0,1,13,-12}},
        {6, {0,1,13,14}}, {16, {0,-12,-13,-25}},
        {26, {0,1,13,14}}, {36, {0,-12,-13,-25}},
    };
    std::vector<int> numbers = assembly_info.at(twisting_value_);

    Tetrixpiece* part_1 = current_.at(0);
    int px = part_1->position_on_x();
    int py = part_1->position_on_y();
    px /= SQUARE_SIDE;
    py /= SQUARE_SIDE;

    std::vector<int> pos_x;
    std::vector<int> pos_y;

    for (unsigned int i = 0; i < 4; ++i) {
        Tetrixpiece* part = current_.at(i);
        pos_x.push_back(part->position_on_x());
        pos_y.push_back(part->position_on_y());
    }

    for (unsigned int i = 0; i < 4;++i) {
        Tetrixpiece* part = current_.at(i);
        int location = numbers.at(i);
        int x = location % 12 + px;
        int y = location / 12 + py;
        int resultX = x * SQUARE_SIDE;
        int resultY = y * SQUARE_SIDE;
        if (0 <= resultX and resultX <= 220 and 0 <= resultY and resultY <= 460) {
            if (map_of_tetris_.count(resultY * 1000 + resultX)) {
                for (unsigned int i = 0; i < 4;++i) {
                    Tetrixpiece* piece = current_.at(i);
                    piece->setX(pos_x.at(i));
                    piece->setY(pos_y.at(i));
                }
                return false;;
            } else {
                part->setX(resultX);
                part->setY(resultY);
            }
        } else {
            for (unsigned int i = 0; i < 4;++i) {
                Tetrixpiece* piece = current_.at(i);
                piece->setX(pos_x.at(i));
                piece->setY(pos_y.at(i));
            }
            return false;
        }
    }
    return true;
}
*/

// if there is anything, stopped over block 21 game is lost.
// from down
bool MainWindow::game_is_lost()
{
    for (int i = 0; i < COLUMNS; ++i) {
        int result = 2 * SQUARE_SIDE * multiplier + SQUARE_SIDE * i;
        if (map_of_tetris_.count(result)) {
            ui->game_over_label->show();
            on_reset_button_clicked();
            return true;
        }
    }
    return false;
}

// clears board from tetrimos and deletes them.
void MainWindow::clear_board()
{
    scene_->clear();
    for (Tetrixpiece* piece : current_) {
        delete piece;
    }
    for (Tetrixpiece* piece : next_) {
        delete piece;
    }
    for (auto part : map_of_tetris_) {
        delete part.second;
    }
    current_.clear();
    next_.clear();
    map_of_tetris_.clear();
}

// Main functio to move tetriminos and game logic.
void MainWindow::tetrimino_move()
{
    if (timer_.interval() == 1000) {
        while (is_movable('S')) {
            move_down();
        }
        for (unsigned int i = 0; i < 4; ++i) {
            Tetrixpiece* piece = current_.at(i);
            map_of_tetris_.insert({piece->exact_position(), piece});
        }
        current_.clear();

        while (remove_full_lines()) {
            gravity();
        }
        add_current();
        timer_.setInterval(game_speed);

    }
    if (is_movable('S')) {
        for (unsigned int i = 0; i < 4; ++i) {
            Tetrixpiece* piece = current_.at(i);
            QGraphicsRectItem* part = piece->returnPointer();
            part->moveBy(0, STEP);
            piece->moving_piece('S');
        }
    }
    if ((!is_movable('S'))){
        timer_.setInterval(1000);
        if (game_is_lost()) {
            timer_.stop();
        }
    }
}

// checks if you can move current tetriminos to heading way.
bool MainWindow::is_movable(char heading)
{
    if (! paused_) {
        if (heading == 'S') { // DOWN or SOUTH
            for (unsigned int i = 0; i < 4; ++i) {
                Tetrixpiece* piece = current_.at(i);
                if(piece->position_on_y() >= BORDER_DOWN - SQUARE_SIDE) {
                    return false;
                }
                if (map_of_tetris_.count(piece->exact_position()
                                         + SQUARE_SIDE * multiplier)) {
                    return false;
                }
            }
        } else if (heading == 'D') { // RIGHT or WEST
            for (unsigned int i = 0; i < 4; ++i) {
                Tetrixpiece* piece = current_.at(i);
                if(piece->position_on_x() >= BORDER_RIGHT - SQUARE_SIDE) {
                    return false;
                }
                if (map_of_tetris_.count(piece->exact_position() + SQUARE_SIDE)) {
                    return false;
                }
            }
        } else if (heading == 'A') { // LEFT or EAST
            for (unsigned int i = 0; i < 4; ++i) {
                Tetrixpiece* piece = current_.at(i);
                if(piece->position_on_x() <= BORDER_LEFT) {
                    return false;
                }
                if (map_of_tetris_.count(piece->exact_position() - SQUARE_SIDE)) {
                    return false;
                }
            }
        } else {
            return false;
        }
        return true;
    }
    return false;
}

// Update QLCD screens.
void MainWindow::update_seconds()
{
    if (! paused_) {
        ++seconds_;
        ui->time_QLCD->display(seconds_);
        ui->score_QLCD->display(score_);
    }
}

// removal of full lines.
bool MainWindow::remove_full_lines()
{
    int full_line = 0;
    for (int y = ROWS; y > 1; --y) {
        if (if_full_line(y)) {
            for (int x = 0; x < COLUMNS; ++x) {
                int result = y * SQUARE_SIDE * multiplier + SQUARE_SIDE * x;
                Tetrixpiece* piece = map_of_tetris_.at(result);
                QGraphicsRectItem* part = piece->returnPointer();
                map_of_tetris_.erase(result);
                scene_->removeItem(part);
                delete piece;
            }
            ++full_line;
        }
    }
    if (full_line > 0) {
        if (full_line == 4) {
            score_ += 400;
        }
        score_ += full_line * 100;
        return true;
    }
    return false;
}

// checks if full line
bool MainWindow::if_full_line(int line)
{
    for (int i = 0; i < COLUMNS; ++i) {
        int result = line * SQUARE_SIDE * multiplier + SQUARE_SIDE * i;
        if (!map_of_tetris_.count(result)) {
                return false;
        }
    }
    return true;
}

// move down after removal of line
void MainWindow::gravity()
{
    for (int y = ROWS; y > 1; --y) {
        for (int x = 0; x < COLUMNS; ++x) {
            int result = y * SQUARE_SIDE * multiplier + SQUARE_SIDE * x;
            if (map_of_tetris_.count(result)) {
                Tetrixpiece* piece = map_of_tetris_.at(result);
                map_of_tetris_.erase(result);
                gravity_move_down(piece);
            }
        }
    }
}

// helper functio for functio above
void MainWindow::gravity_move_down(Tetrixpiece *piece)
{
    QGraphicsRectItem* part = piece->returnPointer();
    if (piece->position_on_y() < BORDER_DOWN - SQUARE_SIDE) {
        if (!map_of_tetris_.count(piece->exact_position()
                                 + SQUARE_SIDE * multiplier)) {
            piece->moving_piece('S');
            part->moveBy(0, STEP);
        }
    }
    map_of_tetris_.insert({piece->exact_position(), piece});
}

// helper functio for functio above
void MainWindow::move_down()
{
    for (unsigned int i = 0; i < 4; ++i) {
        Tetrixpiece* piece = current_.at(i);
        QGraphicsRectItem* part = piece->returnPointer();
        part->moveBy(0, STEP);
        piece->moving_piece('S');
    }
}

// My extra class this class is charge of game dynamics and keeping book where everything is.
Tetrixpiece::Tetrixpiece(
        QGraphicsRectItem* piece, int coordinate_x, int coordinate_y) :
    piece_(piece), coordinate_x_(coordinate_x), coordinate_y_(coordinate_y)
{
}

Tetrixpiece::~Tetrixpiece()
{
}

QGraphicsRectItem *Tetrixpiece::returnPointer()
{
    return piece_;
}

int Tetrixpiece::position_on_x()
{
    return coordinate_x_;
}

int Tetrixpiece::position_on_y()
{
    return coordinate_y_;
}

int Tetrixpiece::exact_position()
{
    return coordinate_y_ * 1000 + coordinate_x_;
}

void Tetrixpiece::moving_piece(char heading)
{
    int delta_x = 0;
    int delta_y = 0;
    if (heading == 'S') {
        delta_y += STEP;
    } else if (heading == 'A') {
        delta_x -= STEP;
    } else {
        delta_x += STEP;
    }
    coordinate_x_ += delta_x;
    coordinate_y_ += delta_y;
}

void Tetrixpiece::setX(int new_X)
{
    coordinate_x_ = new_X;
}

void Tetrixpiece::setY(int new_Y)
{
    coordinate_y_ = new_Y;
}

void Tetrixpiece::moveby(int deltax, int deltay)
{
    coordinate_x_ += deltax;
    coordinate_y_ += deltay;
}

// Starting game
void MainWindow::on_start_button_clicked()
{
    ui->game_over_label->setDisabled(true);
    paused_ = false;
    game_speed = 500;
    timer_.start(game_speed);
    lap_time_.start(1000);
    tetrimino_make_new();
    add_current();
    seconds_ = 0;
    score_ = 0;
    ui->pause_button->setEnabled(true);
    ui->start_button->setDisabled(true);
}
// Pausing game
void MainWindow::on_pause_button_clicked()
{
    paused_ = true;
    timer_.stop();
    lap_time_.stop();
    ui->continue_button->setEnabled(true);
    ui->pause_button->setDisabled(true);
}

// Starting game over. You have to click start to start the game
void MainWindow::on_reset_button_clicked()
{
    timer_.stop();
    lap_time_.stop();
    clear_board();
    ui->continue_button->setDisabled(true);
    ui->pause_button->setDisabled(true);
    ui->start_button->setEnabled(true);
}
// Quit the game
void MainWindow::on_quit_button_clicked()
{
    MainWindow w;
    w.~MainWindow();
}

// continue playing the game after pause
void MainWindow::on_continue_button_clicked()
{
    paused_ = false;
    timer_.start(game_speed);
    lap_time_.start(1000);
    ui->pause_button->setEnabled(true);
    ui->continue_button->setDisabled(true);
}

// trigger cheat mode
void MainWindow::on_crazy_radio_toggled(bool checked)
{
    if (checked) {
        connect(&timer_, &QTimer::timeout, this, &MainWindow::gravity);
    } else {
        disconnect(&timer_, &QTimer::timeout, this, &MainWindow::gravity);
    }
}
