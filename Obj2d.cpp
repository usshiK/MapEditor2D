/// <summary>
/// 概要　 2D画像クラス
/// 作成者 GS1 04 牛山航平
/// </summary>
#include "pch.h"
#include "Obj2d.h"

/* -- 名前空間を解放 ---- */
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;
using Microsoft::WRL::ComPtr;


Microsoft::WRL::ComPtr<ID3D11Device>	Obj2d::m_d3dDevice;
std::unique_ptr<DirectX::SpriteBatch>	Obj2d::m_spriteBatch;
std::unique_ptr<DirectX::CommonStates>	Obj2d::m_states;

bool Obj2d::CompletedInitialize = false;;

Obj2d::Obj2d()
{
	// スケーリング
	m_scale = DirectX::XMFLOAT2(1.0f, 1.0f);

	// 見えるかどうか
	m_isVisible = true;

	// 色
	m_coler = Colors::White;

	// 表示座標の設定
	m_screenPos = Vector2(0.0f,0.0f);
}


Obj2d::~Obj2d()
{
}


/// <summary>
/// 静的メンバ変数の初期化
/// </summary>
/// <param name="d3dContext">スプライトバッチの生成に必要</param>
/// <param name="d3dDevice">ステイトの生成に必要</param>
void Obj2d::staticInitialize(	Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext,
								Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice)
{
	m_d3dDevice = d3dDevice;
	m_spriteBatch = std::make_unique<SpriteBatch>(d3dContext.Get());
	m_states = make_unique<CommonStates>(m_d3dDevice.Get());

	CompletedInitialize = true;
}


/// <summary>
/// 初期化
/// </summary>
/// <param name="imageFileName">読み込む画像のファイル名</param>
/// <param name="pos">初期位置</param>
void Obj2d::initialize(const wchar_t* imageFileName, DirectX::SimpleMath::Vector2 pos)
{
	// スタティックイニシャライズを終えていなければ、止まる
	assert(CompletedInitialize);

	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_d3dDevice.Get(), imageFileName, nullptr,
			m_texture.ReleaseAndGetAddressOf()));

	ComPtr<ID3D11Resource> resource;
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(m_d3dDevice.Get(), imageFileName,
			resource.GetAddressOf(),
			m_texture.ReleaseAndGetAddressOf()));

	ComPtr<ID3D11Texture2D> texture;
	DX::ThrowIfFailed(resource.As(&texture));

	CD3D11_TEXTURE2D_DESC textureDesc;
	texture->GetDesc(&textureDesc);

	m_origin.x = float(textureDesc.Width / 2);
	m_origin.y = float(textureDesc.Height / 2);

	// 表示座標の設定
	m_screenPos = pos;
}

/// <summary>
/// リセット
/// </summary>
void Obj2d::reset()
{
	m_texture.Reset();
	m_spriteBatch.reset();
	m_states.reset();
}

/// <summary>
/// 描画
/// </summary>
void Obj2d::draw()
{
	// 消えた状態なら何もしない
	if (!m_isVisible)return;

	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());

	m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, m_coler,
		0.f, m_origin,m_scale);

	m_spriteBatch->End();
}

void Obj2d::draw(DirectX::XMFLOAT2 scale)
{
	// 消えた状態なら何もしない
	if (!m_isVisible)return;

	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());

	m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, m_coler,
		0.f, m_origin, scale);

	m_spriteBatch->End();
}





