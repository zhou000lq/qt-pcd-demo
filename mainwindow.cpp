#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("load and show");

    //initialize the cloud viewer
    viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
    viewer->setBackgroundColor(255, 255, 255);
    viewer->resetCamera();

    //initialize the cloud
    cloud = PointCloudT::Ptr(new PointCloudT());

    // bind viewer and qvtk
    ui->qvtkWidget->SetRenderWindow(viewer->getRenderWindow());
    viewer->setupInteractor(ui->qvtkWidget->GetInteractor(), ui->qvtkWidget->GetRenderWindow());
    ui->qvtkWidget->update();

    // connect button and the showCloud function
    connect(ui->load, SIGNAL(clicked()), this, SLOT(showCloud()));
}

void MainWindow::showCloud()
{
    QString path = ui->path->text();
    pcl::io::loadPCDFile<pcl::PointXYZ>(path.toStdString(), *cloud);

    pcl::visualization::PointCloudColorHandlerCustom<PointT> color(cloud, 0, 0, 0);
    viewer->addPointCloud(cloud, color, "cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "cloud");

    ui->qvtkWidget->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
