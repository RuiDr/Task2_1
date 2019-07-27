
// Task2_1View.h: CTask21View 类的接口
//

#pragma once
#define WM_MY_MESSAGE (WM_USER+100);
class CTask21View : public CView
{
protected: // 仅从序列化创建
	CTask21View() noexcept;
	DECLARE_DYNCREATE(CTask21View)
	afx_msg LRESULT OnMessage(WPARAM wParam, LPARAM IParam);

// 特性
public:
	CTask21Doc* GetDocument() const;

// 操作
public:
	HGLRC m_hRC;
	CClientDC* m_pDC;

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CTask21View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	bool setPixelFormat();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnErase();
	afx_msg void OnFilledWith();
	afx_msg void OnTestDialog();
	// 消息处理函数
 afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // Task2_1View.cpp 中的调试版本
inline CTask21Doc* CTask21View::GetDocument() const
   { return reinterpret_cast<CTask21Doc*>(m_pDocument); }
#endif

