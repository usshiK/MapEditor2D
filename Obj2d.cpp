/// <summary>
/// �T�v�@ 2D�摜�N���X
/// �쐬�� GS1 04 ���R�q��
/// </summary>
#include "pch.h"
#include "Obj2d.h"

/* -- ���O��Ԃ���� ---- */
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
	// �X�P�[�����O
	m_scale = DirectX::XMFLOAT2(1.0f, 1.0f);

	// �����邩�ǂ���
	m_isVisible = true;

	// �F
	m_coler = Colors::White;

	// �\�����W�̐ݒ�
	m_screenPos = Vector2(0.0f,0.0f);
}


Obj2d::~Obj2d()
{
}


/// <summary>
/// �ÓI�����o�ϐ��̏�����
/// </summary>
/// <param name="d3dContext">�X�v���C�g�o�b�`�̐����ɕK�v</param>
/// <param name="d3dDevice">�X�e�C�g�̐����ɕK�v</param>
void Obj2d::staticInitialize(	Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext,
								Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice)
{
	m_d3dDevice = d3dDevice;
	m_spriteBatch = std::make_unique<SpriteBatch>(d3dContext.Get());
	m_states = make_unique<CommonStates>(m_d3dDevice.Get());

	CompletedInitialize = true;
}


/// <summary>
/// ������
/// </summary>
/// <param name="imageFileName">�ǂݍ��މ摜�̃t�@�C����</param>
/// <param name="pos">�����ʒu</param>
void Obj2d::initialize(const wchar_t* imageFileName, DirectX::SimpleMath::Vector2 pos)
{
	// �X�^�e�B�b�N�C�j�V�����C�Y���I���Ă��Ȃ���΁A�~�܂�
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

	// �\�����W�̐ݒ�
	m_screenPos = pos;
}

/// <summary>
/// ���Z�b�g
/// </summary>
void Obj2d::reset()
{
	m_texture.Reset();
	m_spriteBatch.reset();
	m_states.reset();
}

/// <summary>
/// �`��
/// </summary>
void Obj2d::draw()
{
	// ��������ԂȂ牽�����Ȃ�
	if (!m_isVisible)return;

	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());

	m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, m_coler,
		0.f, m_origin,m_scale);

	m_spriteBatch->End();
}

void Obj2d::draw(DirectX::XMFLOAT2 scale)
{
	// ��������ԂȂ牽�����Ȃ�
	if (!m_isVisible)return;

	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());

	m_spriteBatch->Draw(m_texture.Get(), m_screenPos, nullptr, m_coler,
		0.f, m_origin, scale);

	m_spriteBatch->End();
}





