
// Task2_1View.h: CTask21View 类的接口
//

#pragma once


class CTask21View : public CView
{
protected: // 仅从序列化创建
	CTask21View() noexcept;
	DECLARE_DYNCREATE(CTask21View)

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
};

#ifndef _DEBUG  // Task2_1View.cpp 中的调试版本
inline CTask21Doc* CTask21View::GetDocument() const
   { return reinterpret_cast<CTask21Doc*>(m_pDocument); }
#endif

