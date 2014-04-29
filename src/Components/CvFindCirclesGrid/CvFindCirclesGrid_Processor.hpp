/*!
 * \file CvFindCirclesGrid_Processor.hpp
 * \brief Circles grid localization component.
 * \date Apr 29, 2014
 * \author lzmuda
 */

#ifndef CVFINDCIRCLESGRID_PROCESSOR_HPP_
#define CVFINDCIRCLESGRID_PROCESSOR_HPP_

#include <boost/shared_ptr.hpp>
#include "Component_Aux.hpp"
#include "Types/Objects3D/Chessboard.hpp"
#include "Types/ImagePosition.hpp"
#include "Types/Drawable.hpp"
#include "Timer.hpp"
#include "Property.hpp"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Processors {
namespace CvFindCirclesGrid {

using namespace cv;


#define ELEMS BOOST_PP_TUPLE_TO_LIST(5, (NEAREST, LINEAR, AREA, CUBIC, LANCZOS4))
GENERATE_ENUM_TRANSLATOR(InterpolationTranslator, int, ELEMS, INTER_);

/*

class InterpolationTranslator {
public:
	static int fromStr(const std::string & s)
	{
		if (s == "NEAREST")
			return INTER_NEAREST;
		else if (s == "LINEAR")
			return INTER_LINEAR;
		else if (s == "AREA")
			return INTER_AREA;
		else if (s == "CUBIC")
			return INTER_CUBIC;
		else if (s == "LANCZOS4")
			return INTER_LANCZOS4;
		else
			return INTER_NEAREST;
	}

	static std::string toStr(int t)
	{
		switch (t)
		{
			case INTER_NEAREST:
				return "NEAREST";
			case INTER_LINEAR:
				return "LINEAR";
			case INTER_AREA:
				return "AREA";
			case INTER_CUBIC:
				return "CUBIC";
			case INTER_LANCZOS4:
				return "LANCZOS4";
			default:
				return "NEAREST";
		}
	}
};*/

class CvFindCirclesGrid_Processor: public Base::Component
{
public:
	CvFindCirclesGrid_Processor(const std::string & name = "");
	virtual ~CvFindCirclesGrid_Processor();

	/*!
	 * Prepares communication interface.
	 */
	virtual void prepareInterface();


protected:
	/*!
	 * Method called when component is started
	 * \return true on success
	 */
	virtual bool onStart();

	/*!
	 * Method called when component is stopped
	 * \return true on success
	 */
	virtual bool onStop();

	/*!
	 * Method called when component is initialized
	 * \return true on success
	 */
	virtual bool onInit();

	/*!
	 * Method called when component is finished
	 * \return true on success
	 */
	virtual bool onFinish();

	/*!
	 * Method called when step is called
	 * \return true on success
	 */
	virtual bool onStep();


private:
	void onNewImage();

	void initChessboard();

	/** New image event handler. */
	Base::EventHandler <CvFindCirclesGrid_Processor> h_onNewImage;
	/** Image stream. */
	Base::DataStreamIn <cv::Mat> in_img;
	/** Chessboard stream. */
	Base::DataStreamOut <Types::Objects3D::Chessboard> out_chessboard;
	Base::DataStreamOut <Types::ImagePosition> out_imagePosition;

	Base::DataStreamOut <cv::Mat> out_img;

	/** Located corners.*/
	std::vector<cv::Point2f> corners;

	int findChessboardCornersFlags;

	Common::Timer timer;

	boost::shared_ptr<Types::Objects3D::Chessboard> chessboard;

	cv::Mat sub_img;

	Base::Property<bool> prop_subpix;
	Base::Property<int> prop_subpix_window;
	Base::Property<bool> prop_scale;
	Base::Property<int> prop_scale_factor;
	Base::Property<int> prop_width;
	Base::Property<int> prop_height;
	Base::Property<float> prop_square_width;
	Base::Property<float> prop_square_height;

	Base::Property<bool> prop_fastCheck;
	Base::Property<bool> prop_filterQuads;
	Base::Property<bool> prop_adaptiveThreshold;
	Base::Property<bool> prop_normalizeImage;

	Base::Property<int, InterpolationTranslator> prop_interpolation_type;

	// TODO: add unit types: found and not found

	void sizeCallback(int old_value, int new_value);
	void flagsCallback(bool old_value, bool new_value);
};

} // namespace CvFindCirclesGrid {

} // namespace Processors {

REGISTER_COMPONENT("CvFindCirclesGrid", Processors::CvFindCirclesGrid::CvFindCirclesGrid_Processor)

#endif /* CVFINDCIRCLESGRID_PROCESSOR_HPP_ */
