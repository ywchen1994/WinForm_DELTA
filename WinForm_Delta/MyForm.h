#pragma once
#include<iostream>
#include"cv.h"
#include"highgui.h"
#include"KinectCapture.h"
#include "modbus.h"
namespace WinForm_Delta {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace cv;
	using namespace std;
	KinectCapture kinect;
	modbus_t *mb;
	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		mb = modbus_new_tcp("192.168.1.3", 502);
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  Btn_opnKinect;
	private: System::Windows::Forms::PictureBox^  picBox_Depth;
	protected:

	protected:

	private: System::Windows::Forms::Timer^  Timer_Kinect;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->Btn_opnKinect = (gcnew System::Windows::Forms::Button());
			this->picBox_Depth = (gcnew System::Windows::Forms::PictureBox());
			this->Timer_Kinect = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBox_Depth))->BeginInit();
			this->SuspendLayout();
			// 
			// Btn_opnKinect
			// 
			this->Btn_opnKinect->Location = System::Drawing::Point(570, 12);
			this->Btn_opnKinect->Name = L"Btn_opnKinect";
			this->Btn_opnKinect->Size = System::Drawing::Size(75, 23);
			this->Btn_opnKinect->TabIndex = 0;
			this->Btn_opnKinect->Text = L"opnKinect";
			this->Btn_opnKinect->UseVisualStyleBackColor = true;
			this->Btn_opnKinect->Click += gcnew System::EventHandler(this, &MyForm::Btn_opnKinect_Click);
			// 
			// picBox_Depth
			// 
			this->picBox_Depth->Location = System::Drawing::Point(12, 12);
			this->picBox_Depth->Name = L"picBox_Depth";
			this->picBox_Depth->Size = System::Drawing::Size(512, 424);
			this->picBox_Depth->TabIndex = 1;
			this->picBox_Depth->TabStop = false;
			// 
			// Timer_Kinect
			// 
			this->Timer_Kinect->Interval = 10;
			this->Timer_Kinect->Tick += gcnew System::EventHandler(this, &MyForm::Timer_Kinect_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1322, 617);
			this->Controls->Add(this->picBox_Depth);
			this->Controls->Add(this->Btn_opnKinect);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBox_Depth))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	public:void ShowImage(System::Windows::Forms::PictureBox^ PBox, cv::Mat Image)
	{

		Mat image_Temp;
		switch (Image.type())
		{
		case CV_8UC4:
			cvtColor(Image, image_Temp, CV_BGRA2BGR);
			break;
		case CV_8UC3:
			image_Temp = Image;
			break;
		case CV_8UC1:
			cvtColor(Image, image_Temp, CV_GRAY2RGB);
			break;
		default:
			break;
		}
		System::IntPtr ptr(image_Temp.ptr());
		System::Drawing::Graphics^ graphics = PBox->CreateGraphics();
		System::Drawing::Bitmap^ b = gcnew System::Drawing::Bitmap(image_Temp.cols, image_Temp.rows, image_Temp.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr);
		TextureBrush ^Brush = gcnew TextureBrush(b);

		System::Drawing::RectangleF rect(0, 0, PBox->Width, PBox->Height);
		graphics->FillRectangle(Brush, rect);
		delete Brush;
		delete graphics;
	}
	private: System::Void Timer_Kinect_Tick(System::Object^  sender, System::EventArgs^  e) {
		Mat Image_Depth = kinect.DepthImage();
		if (!Image_Depth.empty())
			ShowImage(picBox_Depth, Image_Depth);
	}
	private: System::Void Btn_opnKinect_Click(System::Object^  sender, System::EventArgs^  e) {
		kinect.Open(0, 1, 0);
		Timer_Kinect->Start();
	}
	};
}
