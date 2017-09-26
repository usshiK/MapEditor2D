/// <summary>
/// �T�v�@ 2D�摜�N���X
/// �쐬�� GS1 04 ���R�q��
/// </summary>

/* �|�| �w�b�_�[�̃C���N���[�h �|�|�|�| */
#pragma once
#include "SpriteBatch.h"
#include <SimpleMath.h>
#include <CommonStates.h>
#include "WICTextureLoader.h"

class Obj2d
{
protected:
	static bool CompletedInitialize;							// staticInitialize���I���Ă��邩�ǂ����̃t���O

	static Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;
	static std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	static std::unique_ptr<DirectX::CommonStates> m_states;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;	// �摜�f�[�^
	DirectX::XMVECTOR m_coler;									// �摜�̐F����
	bool m_isVisible;											// �����邩�ǂ���


	DirectX::SimpleMath::Vector2 m_origin;						// ���S�_
	DirectX::SimpleMath::Vector2 m_screenPos;					// �\���ʒu
	float m_rotation;											// ��]
	DirectX::XMFLOAT2 m_scale;									// �摜�̃X�P�[�����O


public:
	Obj2d();
	virtual ~Obj2d();

	// ������
	virtual void initialize(const wchar_t* imageFileName,
							DirectX::SimpleMath::Vector2 pos = DirectX::SimpleMath::Vector2());

	// ���Z�b�g
	virtual void reset();

	// �ÓI�����o�̏�����
	static void staticInitialize(	Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext,
									Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice);
	// �`��
	virtual void draw();
	virtual void draw(DirectX::XMFLOAT2 scale);
	virtual void setColer(DirectX::XMVECTOR coler) { m_coler = coler; };				// �F��ς���
	virtual void setVisible(bool visible) { m_isVisible = visible; };					// �����邩�ǂ���

	// �Z�b�^�[
	virtual void setPosition(DirectX::SimpleMath::Vector2 pos) {m_screenPos = pos;};	// �\���ʒu
			void setScale(DirectX::XMFLOAT2 scale) {m_scale = scale;};						// �X�P�[�����O

	// �Q�b�^�[
	DirectX::SimpleMath::Vector2 getPos() { return m_screenPos; };
};

