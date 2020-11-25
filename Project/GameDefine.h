#pragma once

#include	"MofSip.h"

#define		GAMEFRAMETIME			(1.0f / 60.0f)

//�d��
#define		GRAVITY					(0.01f)

//���b�V���|�C���^
using CMeshPtr = std::shared_ptr<CMeshContainer>;

//���b�V���A�Z�b�g
using CMeshAsset = CAssetBase<std::string, CMeshContainer>;

//�A�Z�b�g�A�N�Z�X�p�}�N��
#define MeshAsset(key) CMeshAsset::GetAsset(key)