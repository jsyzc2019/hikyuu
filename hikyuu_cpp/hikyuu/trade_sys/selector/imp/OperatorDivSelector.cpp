/*
 *  Copyright (c) 2024 hikyuu.org
 *
 *  Created on: 2024-05-27
 *      Author: fasiondog
 */

#include "OperatorDivSelector.h"

#if HKU_SUPPORT_SERIALIZATION
BOOST_CLASS_EXPORT(hku::OperatorDivSelector)
#endif

namespace hku {

SystemWeightList OperatorDivSelector::getSelected(Datetime date) {
    SystemWeightList ret;
    HKU_IF_RETURN(!m_se1 || !m_se2, ret);

    SystemWeightList sws1, sws2;
    if (m_se1) {
        sws1 = m_se1->getSelected(date);
    }
    if (m_se2) {
        sws2 = m_se2->getSelected(date);
    }

    HKU_IF_RETURN(sws1.empty() || sws2.empty(), ret);

    unordered_map<System*, SystemWeight*> sw_dict1;
    for (auto& sw : sws1) {
        sw_dict1[sw.sys.get()] = &sw;
    }

    SystemWeight tmp;
    unordered_map<System*, SystemWeight*> sw_dict2;
    unordered_map<System*, SystemWeight*>::iterator iter;
    for (auto& sw : sws2) {
        iter = sw_dict1.find(sw.sys.get());
        tmp.sys = sw.sys;
        if (iter != sw_dict1.end()) {
            tmp.weight = std::isnan(sw.weight) ? sw.weight : iter->second->weight / sw.weight;
        } else {
            tmp.weight = 1.0 / sw.weight;
        }
        auto& back = ret.emplace_back(std::move(tmp));
        sw_dict2[back.sys.get()] = &back;
    }

    for (auto& sw : sws1) {
        iter = sw_dict2.find(sw.sys.get());
        if (iter == sw_dict2.end()) {
            ret.emplace_back(std::move(sw));
        }
    }

    std::sort(ret.begin(), ret.end(), [](const SystemWeight& a, const SystemWeight& b) {
        if (std::isnan(a.weight) && std::isnan(b.weight)) {
            return false;
        } else if (!std::isnan(a.weight) && std::isnan(b.weight)) {
            return true;
        } else if (std::isnan(a.weight) && !std::isnan(b.weight)) {
            return false;
        }
        return a.weight > b.weight;
    });

    return ret;
}

HKU_API SelectorPtr operator/(const SelectorPtr& se1, const SelectorPtr& se2) {
    return make_shared<OperatorDivSelector>(se1, se2);
}

}  // namespace hku