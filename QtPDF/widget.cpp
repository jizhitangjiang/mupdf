#include "widget.h"
#include "ui_widget.h"

extern "C" {
#include "fitz.h"
#include "fitz-internal.h"
}

#include <QDebug>
#include <QImage>
#include <QPainter>

extern fz_colorspace *fz_device_rgb;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mupdf();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mupdf()
{
    fz_context *ctx;
    fz_document *doc;
    fz_matrix ctm;//第一页为0

    //创建上下文
    ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
    if (!ctx)
    {
        return;
    }

    QString pdfPath = "D:\\123.pdf";
    //打开文档
    fz_try(ctx)
        doc = fz_open_document(ctx, pdfPath.toLocal8Bit().data());
    fz_catch(ctx)
    {
        fz_free_context(ctx);
        return;
    }

    //取得总的页数
    int page_count = page_count = fz_count_pages(doc);


    //计算缩放以及旋转
    ctm = fz_scale(1.0, 1.0);
    ctm = fz_rotate(0);

    //渲染pixmap
    fz_page *page = fz_load_page(doc, 0);
    fz_rect rect = fz_bound_page(doc, page);
    fz_bbox box = fz_round_rect(rect);

    QString colorDevice = "DeviceRGB";
    fz_pixmap *pix = fz_new_pixmap_with_bbox(ctx, fz_find_device_colorspace(ctx, colorDevice.toLocal8Bit().data()), box);
    fz_clear_pixmap_with_value(ctx, pix, 0xff);

    fz_device *dev = fz_new_draw_device(ctx, pix);
    fz_run_page(doc, page, dev, ctm, NULL);
    fz_free_device(dev);

    //保存图片
    QString savePath = "D://temp.png";
    fz_write_png(ctx, pix, savePath.toLocal8Bit().data(), 0);


     //回收内存
    fz_drop_pixmap(ctx, pix);
    fz_close_document(doc);
    fz_free_context(ctx);
}
