// Copyright 2016 The PiCollectionSaver Authors. All rights reserved.
// Use of this source code is governed by a GNU V3.0 license that can be
// found in the LICENSE file.

#include "deviant_html.h"
#include <regex>

extern shared_ptr<ISiteInfo> g_SiteInfo;
typedef const wchar_t* cwp;


shared_ptr<IHtmlPageElm> IHtmlPageElmCtr(const wstring &strHtml)
{
    shared_ptr<IHtmlPageElm> retVal(new DeviantHtmlPageElmt(strHtml));
    return retVal;
}

DeviantHtmlPageElmt::DeviantHtmlPageElmt(const wstring &strHtml)
    : m_iTotalPhotoCount(-1)
{
    assert(!strHtml.empty());
    m_strHtml = strHtml;
    PreprocessPage();
}



// ============================== main user page ==============================

// <h1><span class="username-with-symbol u"><a class="u regular username"
// href="http://adam-varga.deviantart.com">UserName</a>
static cwp c_rgxUserName = L"<h1>[ ]*<span class=\"username-with-symbol u\">"
                           "[ ]*<a class[^>]+>[ ]*([^ ]+)[ ]*</a>";
wstring DeviantHtmlPageElmt::GetUserName() const
{
    wstring retVal;
    wsmatch match;
    if (regex_search(m_strHtml, match, wregex(c_rgxUserName))
            && match.size() == 2) {
        retVal = match[1].str();
    } else {
        throw parse_ex(L"No or more than one search pattern(:"
                       + to_wstring(__LINE__) + L"): "
                       + wstring(c_rgxUserName), m_strHtml);
    }
    return retVal;
}

// <strong>Last Visit: 2 hours ago</strong>
static cwp c_rgxLastVisit = L"<strong>Last Visit:[ ]*([^<]+)</strong>";
wstring DeviantHtmlPageElmt::GetLastActivityTime() const
{
    wstring retVal;
    wsmatch match;
    if (regex_search(m_strHtml, match, wregex(c_rgxLastVisit))
            && match.size() == 2) {
        retVal = match[1].str();
    } else {
        throw parse_ex(L"No or more than one search pattern(:"
                       + to_wstring(__LINE__) + L"): "
                       + wstring(c_rgxLastVisit), m_strHtml);
    }
    return retVal;
}

wstring DeviantHtmlPageElmt::GetFirstCommonAlbumUrl() const
{
    auto userName = GetUserName();
    wstring retVal = g_SiteInfo->GetProtocol() + userName + L"."
            + g_SiteInfo->GetHostName() + L"/gallery/?catpath=/";
    return retVal;
}

wstring DeviantHtmlPageElmt::GetNextCommonAlbumUrl(const wstring &strCurAlbmUrl,
                                                   int iPicOnPageCnt)
{
    wstring retVal;
    wsmatch match;
    if (regex_search(strCurAlbmUrl, match, wregex(L"&offset=([0-9]+)"))
            && match.size() == 2) {
        int offs = stoi(match[1].str());
        retVal = regex_replace(strCurAlbmUrl, wregex(L"&offset=[0-9]+"),
                               L"&offset=" + to_wstring(offs + iPicOnPageCnt));

    } else {
        assert(strCurAlbmUrl.find(L"&offset=") == wstring::npos);
        retVal = strCurAlbmUrl + L"&offset=" + to_wstring(iPicOnPageCnt);
    }
    return retVal;
}



// ============================== album page ==============================
// <div class="tt-a tt-fh" collect_rid="1:631" ...
// <a class="thumb" href="http://userid.deviantart.com/art/picture"
static cwp c_rgxPicInAlbum1 = L"<div class=\"tt-a tt-fh[^<]*<span[^<]*<span"
                             "[^<]*<span[^<]*<a[ ]+class=\"thumb[^\"]*\"[ ]+href=\"([^\"]+)\"";
static cwp c_rgxPicInAlbum2 = L"<div class=\"tt-a tt-fh[^<]*<span[^<]*<span"
                             "[^<]*<span[^<]*</span[^<]*<span[^<]*<a[ ]+class=\"thumb[^\"]*\"[ ]+href=\"([^\"]+)\"";
list<wstring> DeviantHtmlPageElmt::GetPicPageUrlsList() const
{
    list<wstring> lstRet;
    wsmatch *match, match1, match2;
    auto itB = m_strHtml.cbegin();
    for (;; itB += match->position() + match->length()) {
        regex_search(itB, m_strHtml.cend(), match1, wregex(c_rgxPicInAlbum1));
        regex_search(itB, m_strHtml.cend(), match2, wregex(c_rgxPicInAlbum2));
        if (!match1.empty() && !match2.empty()) {
            match1.position() > match2.position()
                    ? match = &match2 : match = &match1;
        } else if (!match1.empty()) {
            match = &match1;
        } else if (!match2.empty()) {
            match = &match2;
        } else {
            break;
        }
        lstRet.push_back((*match)[1].str());
    }
//TODO: uncomment and add album implementation(depended on total user pictures)
//    if (lstRet.empty()) {
//        throw parse_ex(L"No elements for search pattern(:"
//                       + to_wstring(__LINE__) + L"): "
//                       + wstring(c_rgxPicInAlbum1), m_strHtml);
//    }
    return lstRet;
}


// ============================== pic page ==============================
// <span class="by">by</span> <span class="username-with-symbol u"> <a class=
// "u regular username" href="http://adam-varga.deviantart.com/">UserName</a>
static cwp c_rgxByUserName = L"<span class=\"by\">[^<]+</span>[ ]*<span "
                             "class=\"username-with-symbol u\">"
                             "[ ]*<a class[^>]+>[ ]*([^ <]+)[ ]*</a>";
wstring DeviantHtmlPageElmt::GetUserIdPicPage() const
{
    wstring retVal;
    wsmatch match;
    if (regex_search(m_strHtml, match, wregex(c_rgxByUserName))
            && match.size() == 2) {
        retVal = match[1].str();
    } else {
        throw parse_ex(L"No or more than one search pattern(:"
                       + to_wstring(__LINE__) + L"): "
                       + wstring(c_rgxByUserName), m_strHtml);
    }
    return retVal;
}

// <img collect_rid="1:57" src="http://img11.deviantart.net/e8c0/i/20/image.png"
// data-embed-format="thumb" width="1600" height="900" alt="Image By User"
// class="dev-content-full ">
static cwp c_rgxImage = L"<img[^>]*src=\"([^\"]+)\"[^>]*"
                        "class=\"dev-content-full[ ]*\">";
wstring DeviantHtmlPageElmt::GetBestPossibleDirectPicUrl() const
{
    wstring retVal;
    wsmatch match;
    if (regex_search(m_strHtml, match, wregex(c_rgxImage))
            && match.size() == 2) {
        retVal = match[1].str();
    } else {
        throw parse_ex(L"No or more than one search pattern(:"
                       + to_wstring(__LINE__) + L"): "
                       + wstring(c_rgxImage), m_strHtml);
    }
    return retVal;
}

// <img collect_rid="1:57" src="http://pre12.deviantart.net/3d5a/i/20/image.png"
// data-embed-format="thumb" width="1192" height="670" alt="Image By User"
// class="dev-content-normal ">
static cwp c_rgxImagePreview = L"<img[^>]*src=\"([^\"]+)\"[^>]*"
                               "class=\"dev-content-normal[ ]*\">";
wstring DeviantHtmlPageElmt::GetShownInBrowserDirectPicUrl() const
{
    wstring retVal;
    wsmatch match;
    if (regex_search(m_strHtml, match, wregex(c_rgxImagePreview))
            && match.size() == 2) {
        retVal = match[1].str();
    } else {
        throw parse_ex(L"No or more than one search pattern(:"
                       + to_wstring(__LINE__) + L"): "
                       + wstring(c_rgxImagePreview), m_strHtml);
    }
    return retVal;
}

// <span class="tighttt"><strong>83 </strong> Deviations</span>
static cwp c_rgxPicCount = L"class=\"tighttt\"[>< ]+strong[> ]+"
                           "([0-9]+)[ </]+strong[ >]+Deviations";
int DeviantHtmlPageElmt::GetTotalPhotoCount()
{
    if (m_iTotalPhotoCount == -1) {
        wsmatch match;
        if (regex_search(m_strHtml, match, wregex(c_rgxPicCount))
                && match.size() == 2) {
            m_iTotalPhotoCount = stoi(match[1].str());
        } else {
            throw parse_ex(L"No or more than one search pattern(:"
                           + to_wstring(__LINE__) + L"): "
                           + wstring(c_rgxPicCount), m_strHtml);
        }
    }
    return m_iTotalPhotoCount;
}

// some preprocessing (replace '\n' '\r' to space, replace more than
// one space and tab to just one)
void DeviantHtmlPageElmt::PreprocessPage()
{
    m_strHtml = regex_replace(m_strHtml, wregex(L"[ \t\r\n]+"), L" ");
}
