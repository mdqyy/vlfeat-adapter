/*
 * basic-adapter.cpp
 *
 *  Created on: May 19, 2013
 *      Author: jieshen
 */

#include "basic-adapter.hpp"
#include "../utils.hpp"

namespace jieshen
{
    BASIC_ADAPTER::BASIC_ADAPTER()
    {
        init();
    }

    BASIC_ADAPTER::BASIC_ADAPTER(const Mat* img)
    {
        init();
        set_image_data(img);
    }

    BASIC_ADAPTER::~BASIC_ADAPTER()
    {
        clear_image_data();
    }

    void BASIC_ADAPTER::init()
    {
        init_image_data();
    }

    void BASIC_ADAPTER::init_image_data()
    {
        m_has_set_image = false;
        m_gray_data = NULL;
        m_img_width = 0;
        m_img_height = 0;
    }

    void BASIC_ADAPTER::clear_image_data()
    {
        if (m_gray_data)
            utils::myfree(&m_gray_data);

        m_img_width = 0;
        m_img_height = 0;
    }

    void BASIC_ADAPTER::set_image_data(const Mat* img)
    {
        assert(img->data);

        img->copyTo(m_org_img);

        Mat gray_img;
        if (img->channels() == 3)
            cv::cvtColor(*img, gray_img, CV_BGR2GRAY);
        else
            gray_img = img->clone();

        gray_img.convertTo(gray_img, CV_32FC1);

        m_img_width = img->cols;
        m_img_height = img->rows;

        const int sz = m_img_width * m_img_height * sizeof(float);

        if (m_gray_data)
            free(m_gray_data);

        m_gray_data = (float*) utils::mymalloc(sz);

        memcpy(m_gray_data, gray_img.data, sz);
    }


    const Mat BASIC_ADAPTER::getImage() const
    {
        return m_org_img;
    }

    void BASIC_ADAPTER::check_image() const
    {
        if (!m_has_set_image)
        {
            std::cerr << "Please set the image for processing" << std::endl;
            exit(-1);
        }
    }
}
