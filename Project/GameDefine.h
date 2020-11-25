#pragma once

#include	"MofSip.h"

#define		GAMEFRAMETIME			(1.0f / 60.0f)

//重力
#define		GRAVITY					(0.01f)

//メッシュポインタ
using CMeshPtr = std::shared_ptr<CMeshContainer>;

//メッシュアセット
using CMeshAsset = CAssetBase<std::string, CMeshContainer>;

//アセットアクセス用マクロ
#define MeshAsset(key) CMeshAsset::GetAsset(key)