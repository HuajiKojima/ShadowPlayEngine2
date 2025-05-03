#pragma once

#define D3D_LOG_HRESULT(hr, message)\
{\
	HRESULT hr_ = (hr);\
	if (FAILED(hr_))\
	{\
		std::string msgStr = std::string(message) + "--HRESULT: " + std::to_string(hr_);\
		LOG_ERROR(msgStr.c_str());\
		p_d3d->m_runningPermission = false;\
		return;\
	}\
}