/// <summary>
/// 概要　 2D画像クラス
/// 作成者 GS1 04 牛山航平
/// </summary>

/* －－ ヘッダーのインクルード －－－－ */
#pragma once
#include "SpriteBatch.h"
#include <SimpleMath.h>
#include <CommonStates.h>
#include "WICTextureLoader.h"

class Obj2d
{
protected:
	static bool CompletedInitialize;							// staticInitializeを終えているかどうかのフラグ

	static Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	static std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	static std::unique_ptr<DirectX::CommonStates> m_states;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;	// 画像データ
	DirectX::XMVECTOR m_coler;									// 画像の色合い
	bool m_isVisible;											// 見えるかどうか


	DirectX::SimpleMath::Vector2 m_origin;						// 中心点
	DirectX::SimpleMath::Vector2 m_screenPos;					// 表示位置
	float m_rotation;											// 回転
	DirectX::XMFLOAT2 m_scale;									// 画像のスケーリング


public:
	Obj2d();
	virtual ~Obj2d();

	// 初期化
	virtual void initialize(const wchar_t* imageFileName,
							DirectX::SimpleMath::Vector2 pos = DirectX::SimpleMath::Vector2());

	// リセット
	virtual void reset();

	// 静的メンバの初期化
	static void staticInitialize(	Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext,
									Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice);
	// 描画
	virtual void draw();
	virtual void draw(DirectX::XMFLOAT2 scale);
	virtual void setColer(DirectX::XMVECTOR coler) { m_coler = coler; };				// 色を変える
	virtual void setVisible(bool visible) { m_isVisible = visible; };					// 見えるかどうか

	// セッター
	virtual void setPosition(DirectX::SimpleMath::Vector2 pos) {m_screenPos = pos;};	// 表示位置
			void setScale(DirectX::XMFLOAT2 scale) {m_scale = scale;};						// スケーリング

	// ゲッター
	DirectX::SimpleMath::Vector2 getPos() { return m_screenPos; };
};

